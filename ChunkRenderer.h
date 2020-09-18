#pragma once

#include"Texture.h"
#include"Model.h"
#include"Camera.h"
#include"SimpleShader.h"
#include"Chunk.h"

class ChunkRenderer 
{
public:
	ChunkRenderer();
	~ChunkRenderer() = default;
	void render(Camera* camera);
private:
	Texture _tex;
	SimpleShader  _shader;
	Model _model;
};
