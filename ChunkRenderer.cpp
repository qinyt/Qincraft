#include"ChunkRenderer.h"
#include"Model.h"
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"World.h"


ChunkRenderer::ChunkRenderer():
	_tex("./Textures/DefaultPack2.png")
{
	auto proj_mat = glm::perspective(glm::radians(60.0f), 1.5f, 0.1f, 100.0f);
	_shader.set_project_mat(proj_mat);

	auto* map = World::get_map();
	for(auto chunk: *map)
	{
		add_chunk(&chunk.second);
		
	}
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
	Model *model = new Model();
	model->add_data(chunk->get_mesh());
	_models.emplace_back(model);
}


void ChunkRenderer::render(Camera* camera) 
{
	_shader.bind();
	_shader.set_model_view_mat(*camera->get_model_view_mat());
	_tex.bind();
	glEnable(GL_CULL_FACE);
	
#if 0	
	model.bind();
	glDrawElements(GL_TRIANGLES, model.get_indices_count(), GL_UNSIGNED_INT, nullptr);
#else	
	for (auto model : _models) 
	{
		model->bind();
		glDrawElements(GL_TRIANGLES, model->get_indices_count(), GL_UNSIGNED_INT, nullptr);
	}
#endif
}