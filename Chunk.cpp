#include"ChunkRenderer.h"
#include"Model.h"
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"World.h"
#include"Chunk.h"


Chunk::Chunk() :
	_world_pos{ 0, 0, 0 },
	_is_meshed(false),
	_aabb({ CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE })
{}

Chunk::Chunk(int posX, int posY, int posZ) :
	_world_pos{ posX, posY, posZ}, 
	_is_meshed(false),
	_aabb({ CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE })
{
	_aabb.update({ 
		static_cast<float>(posX * CHUNK_WIDTH_SIZE), 
		static_cast<float>(posY * CHUNK_WIDTH_SIZE),
		static_cast<float>(posY * CHUNK_WIDTH_SIZE)});
}

Chunk::~Chunk() 
{
	clear_mesh();
}

const AABB& Chunk::get_aabb() 
{
	return _aabb;
}

void Chunk::clear_mesh() 
{
	_mesh.indices.clear();
	_mesh.vertices.clear();
}

Mesh_t* Chunk::get_mesh() 
{
	return &_mesh;
}

BlockType Chunk::get_block_type_within_chunk(int x, int y, int z) const
{
	//already filtered the out of bound situation in cylinder level !!!
	GLuint idx = x + z * CHUNK_WIDTH_SIZE + y * CHUNK_LAYER_SIZE;
	return _blocks[idx].get_type();
}

void Chunk::add_data_to_GPU() 
{
	_model.add_data(&_mesh);
}

Model* Chunk::get_model() 
{
	return &_model;
}
