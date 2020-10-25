#pragma once

#include"Model.h"
#include"Block.h"
#include"Math.h"
#include"ChunkManager.h"

#define CHUNK_WIDTH_SIZE	16
#define CHUNK_LAYER_SIZE	CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE
#define CHUNK_VOLUME		CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE

class Chunk 
{
public:
	Chunk();
	Chunk(GLint posX, GLint posZ);
	~Chunk();
	BlockType get_block_type_within_chunk(GLint x, GLint y, GLint z) const;
	Mesh_t* get_mesh();
	inline math::VectorXZ_t get_pos() { return _world_pos; }
	inline GLint get_posX() { return _world_pos.x; }
	inline GLint get_posZ() { return _world_pos.z; }
	inline bool is_dirty() const { return _is_dirty; } 
	inline bool is_meshed() const { return _is_meshed; }
	inline Block* get_block_ptr()  { return _blocks; }
	inline GLuint* get_height_map() { return _height_map; }
	inline GLint* get_biome_map() { return _biome_map; }
	void mesh();
	void build_block();
	void clear_mesh();
	void add_data_to_GPU();
	Model* get_model();
private:
	math::VectorXZ_t _world_pos;
	Mesh_t _mesh;
	Model _model;
	Block _blocks[CHUNK_VOLUME];
//	static ChunkManager _chunk_manager;
	GLuint _height_map[CHUNK_LAYER_SIZE];
	GLint _biome_map[CHUNK_LAYER_SIZE];
	bool _is_meshed;
	bool _is_dirty; // not used yet;
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
