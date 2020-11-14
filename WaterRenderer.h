#pragma once

#include"Texture.h"
#include"Model.h"
#include"Camera.h"
#include"WaterShader.h"
#include"ChunkShader.h"
#include"Chunk.h"
#include<vector>

class WaterRenderer 
{
public:
	WaterRenderer();
	~WaterRenderer();
	void add_model(Model* model);
	void render(Camera* camera);
private:
	WaterShader _shader;
	//ChunkShader _shader;
	//Texture _tex; use texture from chunk renderer
	std::vector<RenderInfo_t*> _models;
};