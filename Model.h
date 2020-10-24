#pragma once

#include<glm/glm.hpp>
#include"glad\glad.h"
#include<vector>

typedef struct Vertex 
{
	GLfloat	position[3];
	GLfloat	tex_coord[2];
}Vertex_t;

typedef struct Mesh 
{
	std::vector<Vertex_t> vertices;
	std::vector<GLuint>	  indices;
	void add_vert(Vertex_t& vert)	{ vertices.emplace_back(vert); }
	void add_index(GLuint index)	{ indices.emplace_back(index); }
}Mesh_t;

typedef struct RenderInfo 
{
	GLuint vao;
	GLuint indices_count;
	void reset() { vao = 0; indices_count = 0; }
}RenderInfo_t;

#define VERTEX_SLOT		0
#define TEX_COORD_SLOT	1

class Model 
{
public:
	Model();
	~Model();
	void add_data(Mesh_t* mesh);
	void bind();
	void clear_data();
	inline GLuint get_indices_count() { return _render_info.indices_count; }
	inline RenderInfo_t* get_render_info() { return &_render_info; }

private:
	void gen_vao();
	void gen_vbo(Mesh_t* mesh);
	void gen_ebo(Mesh_t* mesh);

	RenderInfo_t _render_info;
	GLuint _vbo;
	GLuint _ebo;

};