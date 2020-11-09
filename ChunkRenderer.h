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
	ChunkRenderer() = delete;
	ChunkRenderer(Camera* camera);
	~ChunkRenderer();
	void add_model(Model* model);
	void render(Camera* camera);
private:
	Texture _tex;
	SimpleShader  _shader;
	std::vector<RenderInfo_t*> _models;
};
