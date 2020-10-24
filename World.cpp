#include"World.h"
#include<chrono>
#include"Game.h"

#define sleep_millisecons(x) std::this_thread::sleep_for(std::chrono::milliseconds(50))

std::unordered_map<math::VectorXZ_t, Chunk> World::map;

#if 1
#define LOCK _chunk_mtx.lock();

#define UNLOCK _chunk_mtx.unlock();
#else
#define LOCK 
#define UNLOCK 
#endif

World::World() :
	_chunk_building_thd([&]()
{
	GLint posX, posZ;
	while (1) 
	{
		posX = (Game::player.get_position()->x) / CHUNK_WIDTH_SIZE;
		posZ = (Game::player.get_position()->z) / CHUNK_WIDTH_SIZE;
		LOCK;
		for(GLint i = -RENDER_DISTANCE; i < RENDER_DISTANCE+1; ++i)
			for (GLint j = -RENDER_DISTANCE; j < RENDER_DISTANCE+1; ++j)
			{
				GLint x = posX + j;
				GLint z = posZ + i;
				if (!is_chunk_exist(x, z)) 
				{
					//TODO: async the process
					Chunk chunk(x, z);
					push_chunk(chunk);
				}
			}
		//GLint posX = (Game::player.get_position()->x) / CHUNK_WIDTH_SIZE;
		//GLint posZ = (Game::player.get_position()->z) / CHUNK_WIDTH_SIZE;
		//LOCK;

		// must add chunk first, THEN mesh. Otherwise, the meshing process is wrong.
		for (GLint i = -RENDER_DISTANCE; i < RENDER_DISTANCE; ++i)
			for (GLint j = -RENDER_DISTANCE; j < RENDER_DISTANCE; ++j)
			{
				GLint x = posX + j;
				GLint z = posZ + i;
				math::VectorXZ_t key = { x, z };
				if (map.find(key) == map.end()) continue;
				auto& chunk = map.at(key);
				if (chunk.is_meshed() == false)
				{
					chunk.mesh();
				}
			}
		//printf("map size: %d\n", map.size());
		UNLOCK;
		sleep_millisecons(10);
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
	if (map.find(key) == map.end())
		return BlockType::AIR;
	Chunk& chunk = map.at(key);

	return chunk.get_block_type_within_chunk(x, y, z);
}

void World::set_chunk_renderer(ChunkRenderer* renderer) 
{
	_chunk_renderer = renderer;
}


void World::update() 
{

}

void World::render() 
{
	GLint posX = (Game::player.get_position()->x) / CHUNK_WIDTH_SIZE;
	GLint posZ = (Game::player.get_position()->z) / CHUNK_WIDTH_SIZE;
	LOCK;
	for (auto iter = map.begin(); iter != map.end();)
	{
		auto& pos = iter->first;
		GLint dx = posX - pos.x;
		GLint dz = posZ - pos.z;
		if ((dx * dx + dz * dz) > 2*RENDER_DISTANCE* RENDER_DISTANCE)
		{
			iter = map.erase(iter);
			continue;
		}
		auto& chunk = iter->second;
		chunk.add_data_to_GPU();
		_chunk_renderer->add_chunk(&chunk);
		++iter;
	}

	//map.clear();
	UNLOCK;
}
