#pragma once

#include"Texture.h"
#include"Model.h"
#include"Camera.h"
#include"ChunkShader.h"
#include"Chunk.h"
#include<vector>
class ChunkRenderer 
{
public:
	ChunkRenderer();
	~ChunkRenderer();
	void add_model(Model* model);
	void render(Camera* camera);
private:
	Texture _tex;
	ChunkShader  _shader;
	std::vector<RenderInfo_t*> _models;
};
