#pragma once

#include"Model.h"
#include"Block.h"

#define CHUNK_WIDTH_SIZE	10
#define CHUNK_LAYER_SIZE	CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE
#define CHUNK_VOLUME		CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE

class Chunk;

class ChunkManager 
{
public:
	ChunkManager() = default;
	~ChunkManager() = default;
	void build_mesh(Chunk* chunk);
private:
	bool is_face_buildable(GLint* dir);
	void try_build_front_face();
	void try_build_back_face();
	void try_build_up_face();
	void try_build_down_face();
	void try_build_left_face();
	void try_build_right_face();
	GLint	_posX, _posY, _posZ;
	Chunk*	_current_chunk;
	GLuint	_current_indice;
	Mesh_t* _mesh;
	TexCoord_t*		_coord;
	TexCoordStep_t* _tex_step; 
};

class Chunk 
{
public:
	Chunk();
	~Chunk();
	BlockType get_block_type_within_chunk(GLint x, GLint y, GLint z) const;
	Mesh_t* get_mesh();
private:
	Mesh_t _mesh;
	Block _blocks[CHUNK_VOLUME];
	static ChunkManager _chunk_manager;
	GLint _posX, _posZ;
};

typedef struct Adjacency 
{
	GLint up[3]    = {  0,  1,  0 };
	GLint down[3]  = {  0, -1,  0 };
	GLint left[3]  = { -1,  0,  0 };
	GLint right[3] = {  1,  0,  0 };
	GLint front[3] = {  0,  0, -1 };
	GLint back[3]  = {  0,  0,  1 };
}Adjacency_t;
