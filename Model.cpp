#include"Model.h"

Model::Model():
    _vao(0),
    _vbo(0),
    _indices_count(0)
{
}

Model::~Model() 
{
    clear_data();
}

void Model::add_data(Mesh_t* mesh) 
{
    if (_vao) clear_data();
    gen_vao();
    gen_vbo(mesh);
    gen_ebo(mesh);
    mesh->vertices.clear();
    mesh->indices.clear();
}

void Model::gen_ebo(Mesh_t* mesh) 
{
    _indices_count = static_cast<GLuint>(mesh->indices.size());
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_count * sizeof(GLuint),
        mesh->indices.data(), GL_STATIC_DRAW);
}

void Model::bind()
{
    glBindVertexArray(_vao);
}

void Model::gen_vao() 
{
    glGenVertexArrays(1, &_vao); 
    glBindVertexArray(_vao);
}

void Model::gen_vbo(Mesh_t* mesh)
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex_t), mesh->vertices.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(VERTEX_SLOT, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (GLvoid*)0);
    glEnableVertexAttribArray(VERTEX_SLOT);

    glVertexAttribPointer(TEX_COORD_SLOT, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(TEX_COORD_SLOT);
}

void Model::clear_data() 
{
    if (_vao)
        glDeleteVertexArrays(1, &_vao);
    if (_vbo)
        glDeleteBuffers(1, &_vbo);
    _indices_count = 0;
}