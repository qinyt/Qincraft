#include"WaterShader.h"

WaterShader::WaterShader():
    Shader("./shaders/Water.vert", "./shaders/Chunk.frag")
{
    getUniforms();
}

WaterShader::~WaterShader() 
{
}

void WaterShader::set_time(GLfloat t) 
{
    loadFloat(_time, t);
}


void WaterShader::set_project_view_mat(glm::mat4& mat) 
{
    loadMatrix4(_location_proj_view, mat);
}

void WaterShader::getUniforms() 
{
    bind();
    _location_proj_view = glGetUniformLocation(m_id, "projViewMatrix");
    _time = glGetUniformLocation(m_id, "globalTime");
}