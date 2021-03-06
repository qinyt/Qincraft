#pragma once

#include<unordered_map>
#include"ChunkCylinder.h"
#include"Math.h"
#include"Camera.h"
#include <thread>
#include<mutex>
//#include"ChunkRenderer.h"

class ChunkRenderer;
class WaterRenderer;

#define CHUNK_CENTER_X 1032
#define CHUNK_CENTER_Z 1014
#define PLAYER_SPAWN_X(x) (x+CHUNK_CENTER_X) * CHUNK_WIDTH_SIZE
#define PLAYER_SPAWN_Y(y)  y + CHUNK_WIDTH_SIZE
#define PLAYER_SPAWN_Z(z) (z+CHUNK_CENTER_Z) * CHUNK_WIDTH_SIZE
#define  WATER_LEVEL 64

class World 
{
public:
	World(Camera* camera);
	~World();
	static void push_chunk(ChunkCylinder& chunk);
	static BlockType get_block_type(int x, int y, int z);
	static bool is_chunk_cylinder_exist(int x, int y);
	static std::unordered_map<math::VectorXZ_t, ChunkCylinder>* get_map();
	static void load_chunk(int x, int z);
	void render(Camera* camera);
	void update();
	void set_chunk_renderer(ChunkRenderer* renderer);
	void set_water_renderer(WaterRenderer* renderer);
private:
	static std::unordered_map<math::VectorXZ_t, ChunkCylinder> map;
	std::thread _chunk_building_thd;
	ChunkRenderer* _chunk_renderer;
	WaterRenderer* _water_renderer;
	std::mutex _chunk_mtx;
	int _render_distance;
};