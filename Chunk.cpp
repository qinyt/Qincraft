#include"Chunk.h"
#include"Math.h"
#include"World.h"
#include<memory>

#define ADD_INDICE GLuint index[6]; \
index[0] = _current_indice + 0; \
index[1] = _current_indice + 1; \
index[2] = _current_indice + 3; \
index[3] = _current_indice + 1; \
index[4] = _current_indice + 2; \
index[5] = _current_indice + 3; \
for (int i = 0; i < 6; ++i) _mesh->add_index(index[i]); \
_current_indice += 4

#define likely(x)  __builtin_expect(!!(x), 1)

//ChunkManager Chunk::chunk_manager;
static ChunkManager chunk_manager;

static Adjacency_t adj;

ChunkManager::ChunkManager() 
{
	_tex_step = Block::block_manager.get_tex_coord_step();
}

void ChunkManager::build_mesh(Chunk* chunk)
{
	_current_chunk = chunk;
	_current_indice = 0;

	GLint world_posX = _current_chunk->get_posX();
	GLint world_posZ = _current_chunk->get_posZ();

	_mesh = _current_chunk->get_mesh();
	//_coord = Block::block_manager.get_tex_coord(World::get_block_type(_posX, _posY, _posZ));

	_coord = Block::block_manager.get_tex_coord(BlockType::DIRT);

	for (_posY = 0; _posY < CHUNK_WIDTH_SIZE; ++_posY) 
	{
		for (_posZ = world_posZ * CHUNK_WIDTH_SIZE; _posZ < world_posZ * CHUNK_WIDTH_SIZE + CHUNK_WIDTH_SIZE; ++_posZ)
		{
			for (_posX = world_posX * CHUNK_WIDTH_SIZE; _posX < world_posX * CHUNK_WIDTH_SIZE + CHUNK_WIDTH_SIZE; ++_posX)
			{
				try_build_front_face();
				try_build_back_face();
				try_build_up_face();
//				try_build_down_face();
				try_build_left_face();
				try_build_right_face();
			}
		}
	}
}

//TODO: optimize
void ChunkManager::try_build_front_face() 
{
	if (!is_face_buildable(adj.front)) return;

	GLfloat x =(GLfloat)_posX;
	GLfloat y =(GLfloat)_posY;
	GLfloat z =(GLfloat)_posZ;
	GLfloat u;
	if (_posY != CHUNK_WIDTH_SIZE - 1)	u = _coord->u2;
	else u = _coord->u1;

	Vertex verts[4];
	verts[3] = { x,			y,				z,		u,					_tex_step->v };
	verts[2] = { x + 1.f,	y,				z,		u + _tex_step->u,	_tex_step->v };
	verts[1] = { x + 1.f,	y + 1.f,		z,		u + _tex_step->u,	0.0f };
	verts[0] = { x,			y + 1.f,		z,		u,					0.0f };
	for (int i = 0; i < 4; ++i)  _mesh->add_vert(verts[i]);

	ADD_INDICE;
}
void ChunkManager::try_build_back_face() 
{
	if (!is_face_buildable(adj.back)) return;

	GLfloat x = (GLfloat)_posX;
	GLfloat y = (GLfloat)_posY;
	GLfloat z = (GLfloat)_posZ;
	GLfloat u;
	if (_posY != CHUNK_WIDTH_SIZE - 1)	u = _coord->u2;
	else u = _coord->u1;

	Vertex verts[4];
	verts[0] = { x,		 y,			z + 1,		u,					_tex_step->v };
	verts[1] = { x + 1,	 y,			z + 1,		u + _tex_step->u,	_tex_step->v };
	verts[2] = { x + 1,	 y + 1.f,	z + 1,		u + _tex_step->u,	0.0f };
	verts[3] = { x,		 y + 1.f,	z + 1,		u,					0.0f };
	for (int i = 0; i < 4; ++i)  _mesh->add_vert(verts[i]);
	
	ADD_INDICE;
}

void ChunkManager::try_build_up_face() 
{
	if (!is_face_buildable(adj.up)) return;

	GLfloat x = (GLfloat)_posX;
	GLfloat y = (GLfloat)_posY;
	GLfloat z = (GLfloat)_posZ;

	Vertex verts[4];
	verts[3] = { x + 0,		y + 1.f,		z,				_coord->u0,					_tex_step->v };
	verts[2] = { x + 1.f,	y + 1.f,		z,				_coord->u0 + _tex_step->u,	_tex_step->v };
	verts[1] = { x + 1.f,	y + 1.f,		z + 1.f,		_coord->u0 + _tex_step->u,	0.0f };
	verts[0] = { x + 0,		y + 1.f,		z + 1.f,		_coord->u0,					0.0f };
	for (int i = 0; i < 4; ++i)
		_mesh->add_vert(verts[i]);

	ADD_INDICE;
}

void ChunkManager::try_build_down_face() 
{
	if (!is_face_buildable(adj.down)) return;

	GLfloat x = (GLfloat)_posX;
	GLfloat y = (GLfloat)_posY;
	GLfloat z = (GLfloat)_posZ;

	Vertex verts[4];
	verts[0] = { x + 0,		y,		z,				_coord->u2,					_tex_step->v };
	verts[1] = { x + 1.f,	y,		z,				_coord->u2 + _tex_step->u,	_tex_step->v };
	verts[2] = { x + 1.f,	y,		z + 1.f,		_coord->u2 + _tex_step->u,	0.0f };
	verts[3] = { x + 0,		y,		z + 1.f,		_coord->u2,					0.0f };
	for (int i = 0; i < 4; ++i)
		_mesh->add_vert(verts[i]);

	ADD_INDICE;
}

void ChunkManager::try_build_left_face() 
{
	if (!is_face_buildable(adj.left)) return;

	GLfloat x = (GLfloat)_posX;
	GLfloat y = (GLfloat)_posY;
	GLfloat z = (GLfloat)_posZ;
	GLfloat u;
	if (_posY != CHUNK_WIDTH_SIZE - 1)	u = _coord->u2;
	else u = _coord->u1;

	Vertex verts[4];
	verts[3] = { x,		y,				z + 1.f,	u,					_tex_step->v };
	verts[2] = { x,		y,				z + 0,		u + _tex_step->u,	_tex_step->v };
	verts[1] = { x,		y + 1.f,		z + 0,		u + _tex_step->u,	0.0f };
	verts[0] = { x,		y + 1.f,		z + 1.f,	u,					0.0f };
	for (int i = 0; i < 4; ++i)
		_mesh->add_vert(verts[i]);

	ADD_INDICE;
}
void ChunkManager::try_build_right_face() 
{
	if (!is_face_buildable(adj.right)) return;

	GLfloat x = (GLfloat)_posX;
	GLfloat y = (GLfloat)_posY;
	GLfloat z = (GLfloat)_posZ;
	GLfloat u;
	if (_posY != CHUNK_WIDTH_SIZE - 1)	u = _coord->u2;
	else u = _coord->u1;

	Vertex verts[4];
	verts[0] = { x + 1.f,	y,			z + 1.f,	u,					_tex_step->v };
	verts[1] = { x + 1.f,	y,			z + 0,		u + _tex_step->u,	_tex_step->v };
	verts[2] = { x + 1.f,	y + 1.f,	z + 0,		u + _tex_step->u,	0.0f };
	verts[3] = { x + 1.f,	y + 1.f,	z + 1.f,	u,					0.0f };
	for (int i = 0; i < 4; ++i)
		_mesh->add_vert(verts[i]);

	ADD_INDICE;
}

bool ChunkManager::is_face_buildable(GLint* dir)
{
	GLint pos[3] = { _posX, _posY, _posZ };
	math::vec3i_add(pos, dir, pos);
	//auto type = World::get_block_type(pos[0], pos[1], pos[2]);
	auto type = _current_chunk->get_block_type_within_chunk(pos[0], pos[1], pos[2]);
	
	if (type != BlockType::AIR) 
	{
		return false;
	} 
	return true;
}

//----------------------------------------------------------------------------------------

Chunk::Chunk() :_world_pos{0,0}
{
	for (int i = 0; i < CHUNK_VOLUME; ++i) 
	{
		_blocks[i] = BlockType::DIRT;
	}
	chunk_manager.build_mesh(this);
}

Chunk::Chunk(GLint posX, GLint posZ) :_world_pos{ posX, posZ }
{
	for (int i = 0; i < CHUNK_VOLUME; ++i)
	{
		_blocks[i] = BlockType::DIRT;
	}
	chunk_manager.build_mesh(this);
}

Chunk::~Chunk() 
{
	_mesh.indices.clear();
	_mesh.vertices.clear();
}

Mesh_t* Chunk::get_mesh() 
{
	return &_mesh;
}


//TODO::update to world scenario where you cross chunks
BlockType Chunk::get_block_type_within_chunk(GLint x, GLint y, GLint z) const
{
	x = x - _world_pos.x * CHUNK_WIDTH_SIZE;
	z = z - _world_pos.z * CHUNK_WIDTH_SIZE;

	if (x < 0 || x >= CHUNK_WIDTH_SIZE) return BlockType::AIR;
	if (y < 0 || y >= CHUNK_WIDTH_SIZE) return BlockType::AIR;
	if (z < 0 || z >= CHUNK_WIDTH_SIZE) return BlockType::AIR;
	
	x = x % CHUNK_WIDTH_SIZE;
	z = z % CHUNK_WIDTH_SIZE;
	
	GLuint idx = x + z * CHUNK_WIDTH_SIZE + y * CHUNK_LAYER_SIZE;

	return _blocks[idx].get_type();
}


