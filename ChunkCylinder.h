#pragma once

#include<vector>
#include"Chunk.h"

class ChunkCylinder 
{
public:
	ChunkCylinder() = delete;
	ChunkCylinder(int x, int z);
	~ChunkCylinder() = default;
	Chunk* get_chunk(int y);
	void add_chunk();
	void add_chunk(Chunk& chunk);
	void add_chunk(int x, int y, int z);
	inline math::VectorXZ_t& get_pos() { return _pos; }
	std::vector<Chunk>& get_chunks() { return _chunks; }
	bool is_meshed();
	void mesh();
	inline void set_max_height(int h) { _max_height = h; }
	inline void set_min_height(int h) { _min_height = h; }
	int get_max_height() { return _max_height; }
	int get_min_height() { return _min_height; }
	BlockType get_block_within(int x, int y, int z);
private:
	void build_blocks();
	std::vector<Chunk> _chunks;
	math::VectorXZ_t _pos;
	int _max_height;
	int _min_height;
	bool _meshed;
};
