#include"SimpleRenderer.h"
#include"Model.h"
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include<memory>

SimpleRenderer::SimpleRenderer():
_tex("./Textures/test.png")
{
	int i;
	Mesh mesh;
	auto id_mat = glm::mat4(1.0f);
	auto proj_mat = glm::perspective(glm::radians(90.0f), 1.5f, 0.1f, 2000.0f);
	_shader.set_model_view_mat(id_mat);
	_shader.set_project_mat(proj_mat);
	
	GLfloat pos[4][3] = 
	{	{-100.f,  100.f, -250.f},
		{-100.f, -100.f, -250.f},
		{ 100.f, -100.f, -250.f},
		{ 100.f,  100.f, -250.f} };
	GLfloat cord[4][2] =
	{	{ 0.f,  1.f},
		{ 0.f,  0.f},
		{ 1.f,  0.f},
		{ 1.f,  1.f} };
	GLuint indices[6] = { 0, 1, 2, 2, 3, 0 };
	Vertex_t verts;
	for (i = 0; i < 4; ++i)
	{
		memcpy(verts.position,  pos[i], 3 * sizeof(GLfloat));
		memcpy(verts.tex_coord, cord[i], 2 * sizeof(GLfloat));
		mesh.add_vert(verts);
	}
	for (i = 0; i < 6; ++i) 
	{
		mesh.add_index(indices[i]);
	}
	_model.add_data(&mesh);
}

SimpleRenderer::~SimpleRenderer() 
{
		
}

void SimpleRenderer::render(Camera* camera)
{
	_shader.bind();
	_shader.set_model_view_mat(*camera->get_model_view_mat());
	_tex.bind();
	_model.bind();
	glDrawElements(GL_TRIANGLES, _model.get_indices_count(), GL_UNSIGNED_INT, nullptr);
}