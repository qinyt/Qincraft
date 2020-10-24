#pragma once

#include"Model.h"
#include"Block.h"
#include"Math.h"
#include"NoiseGenerator.h"

class Chunk;
class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();
	void build_mesh(Chunk* chunk);
	void build_block(Chunk* chunk);
private:
	void build_height_map(GLuint* height_map);
	bool is_face_buildable(GLint* dir);
	void try_build_front_face();
	void try_build_back_face();
	void try_build_up_face();
	void try_build_down_face();
	void try_build_left_face();
	void try_build_right_face();
	GLint	_posX, _posY, _posZ;
	Chunk* _current_chunk;
	GLuint	_current_indice;
	Mesh_t* _mesh;
	TexCoord_t* _coord;
	TexCoordStep_t* _tex_step;
	NoiseGenerator* noiser;
};