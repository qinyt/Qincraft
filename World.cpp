#include"World.h"


std::unordered_map<math::VectorXZ_t, Chunk> World::map;

World::World() 
{
	Chunk chunk(500, 500);
	push_chunk(chunk);
	Chunk chunk1(500+1, 500);
	push_chunk(chunk1);
	Chunk chunk2(500+1, 500+1);
	push_chunk(chunk2);
	Chunk chunk3(500, 500+1);	
	push_chunk(chunk3);

	for (auto& item: map) 
	{
		item.second.mesh();
	}
}

World::~World() {}

std::unordered_map<math::VectorXZ_t, Chunk>* World::get_map() 
{
	return &map;
}


void World::push_chunk(Chunk& chunk) 
{
	map.emplace(chunk.get_pos(), chunk);
}


BlockType World::get_block_type(GLint x, GLint y, GLint z) 
{
	auto world_posX = x / CHUNK_WIDTH_SIZE;
	auto world_posZ = z / CHUNK_WIDTH_SIZE;
	math::VectorXZ_t key = { world_posX, world_posZ };
	//printf("coord: %d, %d, %d\n", x, y, z);
	if (map.find(key) == map.end())
		return BlockType::AIR;
	Chunk& chunk = map.at(key);

	return chunk.get_block_type_within_chunk(x, y, z);
}

