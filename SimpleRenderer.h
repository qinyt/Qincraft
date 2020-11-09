#pragma once
#include"Texture.h"
#include"SimpleShader.h"
#include"Model.h"
#include"Camera.h"

class SimpleRenderer 
{
public:
	SimpleRenderer();
	~SimpleRenderer();
	void render(Camera* camera);
private:
	Texture _tex;
	SimpleShader  _shader;
	Model _model;
};