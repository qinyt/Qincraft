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

//TODO: integrite render info
typedef struct RenderInfo 
{
	GLuint _vao;
	GLuint _indices_count;
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
	inline GLuint get_indices_count() { return _indices_count; }

private:
	void gen_vao();
	void gen_vbo(Mesh_t* mesh);
	void gen_ebo(Mesh_t* mesh);

	GLuint _vao;
	GLuint _vbo;
	GLuint _indices_count;
};