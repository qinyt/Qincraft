#pragma once

#include"Shader.h"
#include"glad\glad.h"

class ChunkShader :public Shader 
{
public:
	ChunkShader();
	~ChunkShader();
	void set_project_view_mat(glm::mat4& mat);
private:
	void getUniforms();
	GLuint _location_proj_view;
};