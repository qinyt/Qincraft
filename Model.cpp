#include"Model.h"

Model::Model():
    _render_info({0,0})
{
}

Model::~Model() 
{
    //clear_data();
}

void Model::add_data(Mesh_t* mesh) 
{
    if (_render_info.vao != 0 ) clear_data();
    gen_vao();
    gen_vbo(mesh);
    gen_ebo(mesh);
}   

void Model::gen_ebo(Mesh_t* mesh) 
{
    GLuint ebo;
    _render_info.indices_count = static_cast<GLuint>(mesh->indices.size());
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _render_info.indices_count * sizeof(GLuint),
        mesh->indices.data(), GL_STATIC_DRAW);
    _buffers.push_back(ebo);
}

void Model::bind()
{
    glBindVertexArray(_render_info.vao);
}

void Model::gen_vao() 
{
    glGenVertexArrays(1, &_render_info.vao);
    glBindVertexArray(_render_info.vao);
}

void Model::gen_vbo(Mesh_t* mesh)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex_t), mesh->vertices.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(VERTEX_SLOT, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (GLvoid*)0);
    glEnableVertexAttribArray(VERTEX_SLOT);

    glVertexAttribPointer(TEX_COORD_SLOT, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(TEX_COORD_SLOT);
    _buffers.push_back(vbo);
}

void Model::clear_data() 
{
    if (_render_info.vao)
        glDeleteVertexArrays(1, &_render_info.vao);

    if (_buffers.size() > 0) 
    {
        glDeleteBuffers(static_cast<GLsizei>(_buffers.size()), _buffers.data());
    }
    _buffers.clear();
    _render_info.reset();
}