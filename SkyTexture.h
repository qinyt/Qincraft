#pragma once

#include"glad\glad.h"
#include"SkyTexture.h"
#include<vector>

class SkyTexture 
{
public:
	SkyTexture();
	~SkyTexture();
	void bind();
	void unbind();
	void init(std::vector<const char*> path);
private:
	GLuint _id;
};