#include"SkyShader.h"


SkyShader::SkyShader():
	Shader("./shaders/Skybox.vert", "./shaders/Skybox.frag")
{
	getUniforms();
}

void SkyShader::set_model_view_mat(glm::mat4& mat) 
{
	loadMatrix4(_locationModelViewMatrix, mat);
}


void SkyShader::getUniforms() 
{
	bind();
	_locationProjectionMatrix = glGetUniformLocation(m_id, "projectionMatrix");
	_locationModelViewMatrix = glGetUniformLocation(m_id, "viewMatrix");
}

void SkyShader::set_project_mat(glm::mat4& mat)
{
	loadMatrix4(_locationProjectionMatrix, mat);
}