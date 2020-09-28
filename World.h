#pragma once

#include<unordered_map>
#include"Chunk.h"
#include"Math.h"

class World 
{
public:
	World();
	~World();
	void push_chunk(Chunk& chunk);
	static BlockType get_block_type(GLint x, GLint y, GLint z);
	static std::unordered_map<math::VectorXZ_t, Chunk>* get_map();
private:
	static std::unordered_map<math::VectorXZ_t, Chunk> map;
};