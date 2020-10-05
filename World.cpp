#include"World.h"
#include<chrono>
#include"Game.h"

#define sleep_millisecons(x) std::this_thread::sleep_for(std::chrono::milliseconds(50))

std::unordered_map<math::VectorXZ_t, Chunk> World::map;

World::World() :
	_chunk_building_thd([&]()
{
	while (1) 
	{
		GLint posX = (Game::player.get_position()->x) / CHUNK_WIDTH_SIZE;
		GLint posZ = (Game::player.get_position()->z) / CHUNK_WIDTH_SIZE;
		for(GLint i = -RENDER_DISTANCE; i < RENDER_DISTANCE; ++i)
			for (GLint j = -RENDER_DISTANCE; j < RENDER_DISTANCE; ++j)
			{
				GLint x = posX + j;
				GLint z = posZ + i;
				if (!is_chunk_exist(x, z)) 
				{
					Chunk chunk(x, z);
					push_chunk(chunk);					
				}
			}
		// must add chunk first, THEN mesh. Otherwise, the meshing process is wrong.
		for (GLint i = -RENDER_DISTANCE; i < RENDER_DISTANCE; ++i)
			for (GLint j = -RENDER_DISTANCE; j < RENDER_DISTANCE; ++j)
			{
				GLint x = posX + j;
				GLint z = posZ + i;
				math::VectorXZ_t key = { x, z };
				auto& chunk = map.at(key);
				if (chunk.is_meshed() == false) 
				{
					chunk.mesh();
				}
			}
		printf("building chunks \n");
		sleep_millisecons(50);
	}
})
{

}

World::~World() 
{
	_chunk_building_thd.join();
}

std::unordered_map<math::VectorXZ_t, Chunk>* World::get_map() 
{
	return &map;
}

bool World::is_chunk_exist(GLint x, GLint y) 
{
	math::VectorXZ_t key = { x, y};
	return (map.find(key) != map.end());
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

