#include"ChunkRenderer.h"
#include"Model.h"
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"World.h"
#include"Chunk.h"

//ChunkManager Chunk::chunk_manager;
static ChunkManager chunk_manager;

Chunk::Chunk() :
	_world_pos{ 0,0 },
	_is_meshed(false),
	_is_dirty(false)
{
	build_block();
}

Chunk::Chunk(GLint posX, GLint posZ) :
	_world_pos{ posX, posZ }, 
	_is_meshed(false),
	_is_dirty(false)
{
	/*for (int i = 0; i < CHUNK_VOLUME; ++i)
	{
		_blocks[i] = BlockType::DIRT;
	}*/
	build_block();
}

void Chunk::build_block()
{
	chunk_manager.build_block(this);
}

void Chunk::mesh() 
{
	chunk_manager.build_mesh(this);
	_is_meshed = true;
}

Chunk::~Chunk() 
{
	clear_mesh();
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

//TODO::update to world scenario where you cross chunks
BlockType Chunk::get_block_type_within_chunk(GLint x, GLint y, GLint z) const
{
	if (y < 0 || y >= CHUNK_WIDTH_SIZE) return BlockType::AIR;
	
	GLint lx = x - _world_pos.x * CHUNK_WIDTH_SIZE;
	GLint lz = z - _world_pos.z * CHUNK_WIDTH_SIZE;

	if (lx < 0 || lx >= CHUNK_WIDTH_SIZE) return World::get_block_type(x, y, z);
	if (lz < 0 || lz >= CHUNK_WIDTH_SIZE) return World::get_block_type(x, y, z);
	
	GLuint idx = lx + lz * CHUNK_WIDTH_SIZE + y * CHUNK_LAYER_SIZE;

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
