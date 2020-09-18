#pragma once
#include"SkyTexture.h"
#include"SimpleShader.h"
#include"Model.h"
#include"Camera.h"

class SkyRenderer
{
public:
	SkyRenderer();
	~SkyRenderer() = default;
	void render(Camera* camera);
private:
	SkyTexture _tex;
	SimpleShader  _shader;
	Model _model;
};
