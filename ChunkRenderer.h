#pragma once

#include"Texture.h"
#include"Model.h"
#include"Camera.h"
#include"SimpleShader.h"
#include"Chunk.h"
#include<vector>
class ChunkRenderer 
{
public:
	ChunkRenderer();
	~ChunkRenderer();
	void add_chunk(Chunk* chunk);
	void render(Camera* camera);
private:
	Texture _tex;
	SimpleShader  _shader;
	std::vector<RenderInfo_t*> _models;
};
