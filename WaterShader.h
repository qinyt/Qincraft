#pragma once

#include"Shader.h"

class WaterShader :public Shader 
{
public:
	WaterShader();
	~WaterShader();
	void set_project_view_mat(glm::mat4& mat);
	void set_time(GLfloat t);
private:
	void getUniforms() override;
	GLuint _time;
	GLuint _location_proj_view;
};

