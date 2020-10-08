#pragma once
#include"SkyTexture.h"
#include"Model.h"
#include"Camera.h"
#include"SkyShader.h"

class SkyRenderer
{
public:
	SkyRenderer();
	~SkyRenderer() = default;
	void render(Camera* camera);
private:
	SkyTexture _tex;
	SkyShader _shader;
	Model _model;
};
