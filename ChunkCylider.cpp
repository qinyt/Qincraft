#include"ChunkCylinder.h"
#include"World.h"


static ChunkManager chunk_manager;

ChunkCylinder::ChunkCylinder(int x, int z)
	:_pos({ x, z })
{
	build_blocks();
}

void ChunkCylinder::build_blocks() 
{
	chunk_manager.build_cylinder(this);
}

Chunk* ChunkCylinder::get_chunk(int y) 
{
	int py = static_cast<int>(y / CHUNK_WIDTH_SIZE);
	for (Chunk& chunk : _chunks) 
	{
		if (chunk.get_pos().y == py) return &chunk;
	}
	Chunk chunk(_pos.x, py, _pos.z);
	_chunks.emplace_back(chunk);
	return &_chunks.back();
}

void ChunkCylinder::add_chunk() 
{
	int top = _max_height / CHUNK_WIDTH_SIZE;
	int btm = _min_height / CHUNK_WIDTH_SIZE;
	for (int i = btm; i <= top; ++i) 
	{
		Chunk chunk(_pos.x, i, _pos.z);
		_chunks.emplace_back(chunk);
	}
}

void ChunkCylinder::add_chunk(Chunk& chunk)
{
	_chunks.emplace_back(chunk);
}

void ChunkCylinder::add_chunk(int x, int y, int z) 
{
	Chunk chunk(x, y, z);
	_chunks.emplace_back(chunk);
}


void ChunkCylinder::mesh(Camera* camera)
{
	for (int z = _pos.z - 1; z <= _pos.z + 1; ++z) 
	{
		for (int x = _pos.x - 1; x <= _pos.x + 1; ++x) 
		{
			World::load_chunk(x, z);
		}
	}
	chunk_manager.build_mesh(this, camera);
}

BlockType ChunkCylinder::get_block_within(int x, int y, int z)
{
	if (y <= WATER_LEVEL) return BlockType::WATER;
	if (y > _max_height) return BlockType::AIR;
	int chunkY = static_cast<int>(y / CHUNK_WIDTH_SIZE);
	for (auto& chunk : _chunks) 
	{
		if (chunk.get_pos().y == chunkY)
		{
			int iy = y - chunkY * CHUNK_WIDTH_SIZE;
			return chunk.get_block_type_within_chunk(x, iy, z);
		}
	}
	return BlockType::MUD;
}
