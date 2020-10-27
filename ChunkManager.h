#pragma once

#include"Model.h"
#include"Block.h"
#include"Math.h"
#include"NoiseGenerator.h"
#include"biome\Biome.h"
#include"biome\DesertBiome.h"
#include"biome\GrasslandBiome.h"
#include"biome\LightForest.h"
#include"biome\OceanBiome.h"
#include"biome\TemperateForestBiome.h"

typedef struct Adjacency
{
	GLint up[3] = { 0,  1,  0 };
	GLint down[3] = { 0, -1,  0 };
	GLint left[3] = { -1,  0,  0 };
	GLint right[3] = { 1,  0,  0 };
	GLint front[3] = { 0,  0, -1 };
	GLint back[3] = { 0,  0,  1 };
}Adjacency_t;

class ChunkCylinder;
class Chunk;

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();
	void build_mesh(ChunkCylinder* cy);
	void build_cylinder(ChunkCylinder* cy);
private:
	void setup_noise();
	void build_block();
	void build_biome_map();
	void build_height_map();
	void get_max_min_height();
	bool is_face_buildable(int* dir);
	void try_build_front_face();
	void try_build_back_face();
	void try_build_up_face();
	void try_build_left_face();
	void try_build_right_face();
	const Biome& getBiome(int x, int z) const;
	GLint	_posX, _posY, _posZ;
	ChunkCylinder* _cur_chunk_cylinder;
	GLuint	_current_indice;
	Mesh_t* _mesh;
	TexCoord_t* _coord;
	TexCoordStep_t* _tex_step;
	NoiseGenerator noiser;

	OceanBiome m_oceanBiome;
	GrasslandBiome m_grassBiome;
	LightForest m_lightForest;
	TemperateForestBiome m_temperateForest;
	DesertBiome m_desertBiome;
};