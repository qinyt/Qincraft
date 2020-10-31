#include"ChunkRenderer.h"
#include"Model.h"
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"World.h"
#include"Application.h"

//ChunkRenderer::ChunkRenderer():
//	_tex("./Textures/DefaultPack2.png")
//{
//	auto proj_mat = glm::perspective(glm::radians(60.0f), 1.5f, 0.1f, 1000.0f);
//	_shader.set_project_mat(proj_mat);
//}

ChunkRenderer::ChunkRenderer(Camera* camera) :
	_tex("./Textures/DefaultPack2.png")
{
	_shader.set_project_mat(camera->get_proj_mat());
}

ChunkRenderer::~ChunkRenderer() 
{
	for (auto model : _models) 
	{
		delete model;
	}
}

void ChunkRenderer::add_chunk(Chunk* chunk)
{
	_models.emplace_back(chunk->get_model()->get_render_info());
}


void ChunkRenderer::render(Camera* camera) 
{	
	if (_models.empty()) return;

	_shader.bind();
	_shader.set_model_view_mat(*camera->get_model_view_mat());
	_tex.bind();
	glEnable(GL_CULL_FACE);
		
	for (auto model : _models) 
	{
#if SHOW_TRI_COUNT
		int count = (int)(model->indices_count / 3);
		if(count!= 0)
		App::tri_count = count;
#endif // SHOW_TRI_COUNT

		glBindVertexArray(model->vao);
		glDrawElements(GL_TRIANGLES, model->indices_count, GL_UNSIGNED_INT, nullptr);
	}
	_models.clear();
}