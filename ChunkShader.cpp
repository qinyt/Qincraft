#include"ChunkShader.h"


ChunkShader::ChunkShader():
	Shader("./shaders/Chunk.vert", "./shaders/Chunk.frag")
{
    getUniforms();
}

ChunkShader::~ChunkShader() {}

void ChunkShader::getUniforms() 
{
    bind();
    _location_proj_view = glGetUniformLocation(m_id, "projViewMatrix;");
}

void ChunkShader::set_project_view_mat(glm::mat4& mat)
{
    loadMatrix4(_location_proj_view, mat);
}
