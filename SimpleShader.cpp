#include"SimpleShader.h"


SimpleShader::SimpleShader():
	Shader("./shaders/Basic.vert", "./shaders/Basic.frag"),
    _locationModelViewMatrix(0),
    _locationProjectionMatrix(0)
{
    getUniforms();
}

SimpleShader::~SimpleShader() {}

void SimpleShader::getUniforms() 
{
    bind();
    _locationProjectionMatrix  = glGetUniformLocation(m_id, "proj9Matrix");
    _locationModelViewMatrix   = glGetUniformLocation(m_id, "modelViewMatrix");
}

void SimpleShader::set_model_view_mat(glm::mat4& mat) 
{
    loadMatrix4(_locationModelViewMatrix, mat);
}

void SimpleShader::set_project_mat(glm::mat4& mat)
{

    loadMatrix4(_locationProjectionMatrix, mat);
}

void SimpleShader::set_project_mat(GLfloat* data) 
{
    glUniformMatrix4fv(_locationProjectionMatrix, 1, GL_FALSE, data);
}

void SimpleShader::set_model_view_mat(GLfloat* data)
{
    glUniformMatrix4fv(_locationModelViewMatrix, 1, GL_FALSE, data);
}