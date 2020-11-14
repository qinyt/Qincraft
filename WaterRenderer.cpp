#include"WaterRenderer.h"
#include"Application.h"

WaterRenderer::WaterRenderer() {}

WaterRenderer::~WaterRenderer() 
{
}

void WaterRenderer::add_model(Model* model) 
{
	_models.push_back(model->get_render_info());
	//printf("water model size: %d\n", _models.size());
}

void WaterRenderer::render(Camera* camera) 
{
	if (_models.empty()) return;

	_shader.bind();
	_shader.set_project_view_mat(*camera->get_proj_view_mat());
	_shader.set_time(App::time_sec_elapsed);
	glEnable(GL_CULL_FACE);
	for (auto& model : _models) 
	{
		glBindVertexArray(model->vao);
		glDrawElements(GL_TRIANGLES, model->indices_count, GL_UNSIGNED_INT, nullptr);
	}
	_models.clear();
}