#include"SkyRenderer.h"

#define SIZE 500.f

SkyRenderer::SkyRenderer() 
{
	std::vector<const char*> path;
	path.emplace_back("./Textures/left.png");
	path.emplace_back("./Textures/right.png");
	path.emplace_back("./Textures/top.png");
	path.emplace_back("./Textures/bottom.png");
	path.emplace_back("./Textures/front.png");
	path.emplace_back("./Textures/back.png");
	_tex.init(path);
	
	int i;
	Mesh mesh;
	auto id_mat = glm::mat4(1.0f);
	//auto proj_mat = glm::perspective(glm::radians(60.0f), 1.5f, -600.0f, 600.0f);
	auto proj_mat = glm::perspective(glm::radians(60.0f), 1.5f, 0.1f, 1000.0f);

	_shader.set_project_mat(proj_mat);

	GLfloat pos[][3] =
	{	
		 SIZE,
		-SIZE,
		-SIZE,
		-SIZE,
		-SIZE,
		-SIZE,
		-SIZE,
		SIZE,
		-SIZE,
		SIZE,
		SIZE,
		-SIZE,

		// Front
		-SIZE,
		-SIZE,
		SIZE,
		SIZE,
		-SIZE,
		SIZE,
		SIZE,
		SIZE,
		SIZE,
		-SIZE,
		SIZE,
		SIZE,

		// Right
		SIZE,
		-SIZE,
		SIZE,
		SIZE,
		-SIZE,
		-SIZE,
		SIZE,
		SIZE,
		-SIZE,
		SIZE,
		SIZE,
		SIZE,

		// Left
		-SIZE,
		-SIZE,
		-SIZE,
		-SIZE,
		-SIZE,
		SIZE,
		-SIZE,
		SIZE,
		SIZE,
		-SIZE,
		SIZE,
		-SIZE,

		// Top
		-SIZE,
		SIZE,
		SIZE,
		SIZE,
		SIZE,
		SIZE,
		SIZE,
		SIZE,
		-SIZE,
		-SIZE,
		SIZE,
		-SIZE,

		// Bottom
		-SIZE,
		-SIZE,
		-SIZE,
		SIZE,
		-SIZE,
		-SIZE,
		SIZE,
		-SIZE,
		SIZE,
		-SIZE,
		-SIZE,
		SIZE,
	};

	GLuint indices[] = 
	{
		0, 1, 2, 2, 3, 0, 
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12, 
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};
	Vertex_t verts;
	for (i = 0; i < 24; ++i)
	{
		memcpy(verts.position, pos[i], 3 * sizeof(GLfloat));
		//memcpy(verts.tex_coord, cord[i], 2 * sizeof(GLfloat));
		mesh.add_vert(verts);
	}
	for (i = 0; i < 36; ++i)
	{
		mesh.add_index(indices[i]);
	}
	_model.add_data(&mesh);
}

void SkyRenderer::render(Camera* camera)
{
	glDisable(GL_CULL_FACE);
	_shader.bind();
	_shader.set_model_view_mat(*camera->get_sky_view_mat());
	_tex.bind();
	_model.bind();
	glDrawElements(GL_TRIANGLES, _model.get_indices_count(), GL_UNSIGNED_INT, nullptr);
}