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
	~ChunkRenderer() = default;
	void add_chunk(Chunk* chunk);
	void render(Camera* camera);
private:
	Texture _tex;
	SimpleShader  _shader;
	std::vector<Model> _models;
};
