#pragma once

#include"Shader.h"
#include"glad\glad.h"

class SimpleShader :public Shader 
{
public:
	SimpleShader();
	~SimpleShader();
	void set_model_view_mat(glm::mat4& mat);
	void set_project_mat(glm::mat4& mat);
	void set_project_mat(GLfloat* data);
	void set_model_view_mat(GLfloat* data);
private:
	void getUniforms();
	GLuint _locationProjectionMatrix;
	GLuint _locationModelViewMatrix;
};