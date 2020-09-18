#pragma once

#include"glad\glad.h"

enum BlockType
{
	 GRASS, WATER, DIRT, STONE, OAKBARK, OAKLEAF, SAND, CACTUS, ROSS, AIR, NUM_OF_BLOCK_TYPE
};

typedef struct TexturePos
{
	GLuint x, y;
}TexturePos_t;

typedef struct TexCoord 
{
	GLfloat u0, v0; //up
	GLfloat u1, v1; //side
	GLfloat u2, v2; //bottom
}TexCoord_t;

typedef struct TexCoordStep
{
	GLfloat u, v;
}TexCoordStep_t;

class BlockManager 
{
public:
	BlockManager();
	~BlockManager() = default;
	void set_width_height(GLuint width, GLuint height);
	TexCoord_t* get_tex_coord(BlockType type);
	inline TexCoordStep_t* get_tex_coord_step() { return &_tex_coord_step; }
private:
	void init_block_tex_pos();
	void init_block_tex_coord();
	TexCoord_t calc_tex_coord(BlockType type);
private:
	GLuint _tex_index_width, _tex_index_height;
	TexCoordStep_t _tex_coord_step;
	TexturePos_t* block_tex_pos; 
	TexCoord_t block_tex_coord[NUM_OF_BLOCK_TYPE - 1];
};

class Block 
{
public:
	Block(BlockType type = AIR);
	~Block() = default;
	TexCoord_t get_tex_coord();
	inline void set_type(BlockType type) { _type = type; }
	inline BlockType get_type() const {  return _type; }
	static BlockManager block_manager;
private:
	BlockType _type;
};