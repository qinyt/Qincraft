#include"ChunkRenderer.h"
#include"Model.h"
#include<glm/glm.hpp>
#include<glm/ext.hpp>


ChunkRenderer::ChunkRenderer():
	_tex("./Textures/DefaultPack2.png")
{
	auto proj_mat = glm::perspective(glm::radians(60.0f), 1.5f, 0.1f, 100.0f);
	_shader.set_project_mat(proj_mat);
	Chunk chunk;
	auto mesh = chunk.get_mesh();
	printf("verts size:%d, indice size:%d\n", mesh->vertices.size(), mesh->indices.size());
	
	_model.add_data(mesh);
}

void ChunkRenderer::render(Camera* camera) 
{
	_shader.bind();
	_shader.set_model_view_mat(*camera->get_model_view_mat());
	_tex.bind();
	_model.bind();
	glEnable(GL_CULL_FACE);
	glDrawElements(GL_TRIANGLES, _model.get_indices_count(), GL_UNSIGNED_INT, nullptr);
}