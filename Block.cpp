#include"Block.h"
#include<stdlib.h>
#include<iostream>

BlockManager Block::block_manager;

BlockManager::BlockManager():_tex_index_width(0), _tex_index_height(0)
{
	set_width_height(16, 16);
	init_block_tex_pos();
	init_block_tex_coord();
}

void BlockManager::init_block_tex_pos()
{
	block_tex_pos = new TexturePos_t[NUM_OF_BLOCK_TYPE - 1]; //air block has no texture

	//TODO: init it all
	block_tex_pos[BlockType::DIRT] = { 0, 0 };
}

void BlockManager::init_block_tex_coord()
{
	//TODO: init it all
	block_tex_coord[BlockType::DIRT] = calc_tex_coord(BlockType::DIRT);
	
	delete[] block_tex_pos;
}
TexCoord_t BlockManager::calc_tex_coord(BlockType type) 
{
	if (_tex_index_width == 0) 
	{
		std::cerr << "texture atlas width not initalized yet";
		exit(0);
	}
	TexCoord_t res;

	res.u0 = (float)block_tex_pos[type].x / (float)_tex_index_width;
	res.v0 = (float)block_tex_pos[type].y / (float)_tex_index_height;
	res.u1 = res.u0 + _tex_coord_step.u;
	res.v1 = res.v0;
	res.u2 = res.u1 + _tex_coord_step.u;
	res.v2 = res.v0;
	return res;
}

TexCoord_t* BlockManager::get_tex_coord(BlockType type) 
{ 
	return &block_tex_coord[type]; 
}

void BlockManager::set_width_height(GLuint width, GLuint height) 
{
	_tex_index_height	=	height; 
	_tex_index_width	=	width; 
	_tex_coord_step.u	=	1 / (GLfloat)width;
	_tex_coord_step.v	=	1 / (GLfloat)height;
}

Block::Block(BlockType type) :
	_type(type)
{

}

TexCoord_t Block::get_tex_coord() 
{
	return *block_manager.get_tex_coord(_type);
}

