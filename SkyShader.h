#pragma once


#include"Shader.h"
#include"glad\glad.h"

class SkyShader :public Shader
{
public:
	SkyShader();
	~SkyShader() = default;
	void set_model_view_mat(glm::mat4& mat);
	void set_project_mat(glm::mat4& mat);

private:
	void getUniforms();
	GLuint _locationProjectionMatrix;
	GLuint _locationModelViewMatrix;
};
