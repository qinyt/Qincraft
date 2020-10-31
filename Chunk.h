#pragma once

#include"Model.h"
#include"Block.h"
#include"Math.h"
#include"ChunkManager.h"
#include"AABB.h"
#include<SFML\Graphics.hpp>

#define CHUNK_WIDTH_SIZE	16
#define CHUNK_LAYER_SIZE	CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE
#define CHUNK_VOLUME		CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE

class Chunk 
{
public:
	Chunk();
	Chunk(int posX,int posY, int posZ);
	~Chunk();
	BlockType get_block_type_within_chunk(int x, int y, int z) const;
	Mesh_t* get_mesh();
	inline sf::Vector3i& get_pos() { return _world_pos; }
	inline Block* get_block_ptr()  { return _blocks; }
	void clear_mesh();
	void add_data_to_GPU();
	Model* get_model();
	const AABB& get_aabb();
	inline bool is_meshed() { return _is_meshed; }
	inline void set_mesh_flag(bool is_meshed) { _is_meshed = is_meshed; }
private:
	sf::Vector3i _world_pos;
	Mesh_t _mesh;
	Model _model;
	Block _blocks[CHUNK_VOLUME];
	bool _is_meshed;
	AABB _aabb;
};


