#include"WaterRenderer.h"

WaterRenderer::WaterRenderer() {}

WaterRenderer::~WaterRenderer() 
{
	for (auto model : _models)
	{
		delete model;
	}
}

void WaterRenderer::add_model(Model* model) 
{
	_models.emplace_back(model->get_render_info());
}

void WaterRenderer::render(Camera* camera) 
{
	if (_models.empty()) return;

	_shader.bind();
	_shader.set_project_view_mat(*camera->get_proj_view_mat());
	glEnable(GL_CULL_FACE);
	for (auto& model : _models) 
	{
		glBindVertexArray(model->vao);
		glDrawElements(GL_TRIANGLES, model->indices_count, GL_UNSIGNED_INT, nullptr);
	}
	_models.clear();
}