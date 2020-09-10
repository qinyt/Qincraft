#pragma once
#include"glad\glad.h"

class Texture 
{
public:
	Texture(const char* path);
	~Texture();
	void bind();
	void unbind();
private:
	void init(const char* path);

	GLuint _id;
};