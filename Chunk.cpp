#include"ChunkRenderer.h"
#include"Model.h"
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"World.h"
#include"Chunk.h"


//Chunk::Chunk() :
//	_world_pos{ 0, 0, 0 },
//	_is_meshed(false),
//	_aabb({ CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE })
//{}

Chunk::Chunk(int posX, int posY, int posZ) :
	_world_pos{ posX, posY, posZ}, 
	_is_meshed(false),
	_aabb({ CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE,CHUNK_WIDTH_SIZE })
{
	_aabb.update({ 
		static_cast<float>(posX * CHUNK_WIDTH_SIZE), 
		static_cast<float>(posY * CHUNK_WIDTH_SIZE),
		static_cast<float>(posZ * CHUNK_WIDTH_SIZE)});
}

Chunk::~Chunk() 
{
	clear_mesh();
}

const AABB& Chunk::get_aabb() 
{
	return _aabb;
}

Mesh_t* Chunk::get_mesh(BlockType block) 
{
	/*if (block == BlockType::WATER)
		return &_meshes.water;*/
	return &_meshes.solid;
}

void Chunk::clear_mesh() 
{
	_meshes.solid.indices.clear();
	_meshes.solid.vertices.clear();
	_meshes.water.indices.clear();
	_meshes.water.vertices.clear();
}


BlockType Chunk::get_block_type_within_chunk(int x, int y, int z) const
{
	//already filtered the out of bound situation in cylinder level !!!
	GLuint idx = x + z * CHUNK_WIDTH_SIZE + y * CHUNK_LAYER_SIZE;
	return _blocks[idx].get_type();
}

void Chunk::add_data_to_GPU() 
{
	_meshes.add_to_model();
}

Meshes_t* Chunk::get_meshes() 
{
	return &_meshes;
}
