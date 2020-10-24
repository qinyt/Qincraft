#include"Chunk.h"
#include"Math.h"
#include"World.h"
#include<memory>
#include"ChunkManager.h"


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

static Adjacency_t adj;

ChunkManager::ChunkManager()
{
	_tex_step = Block::block_manager.get_tex_coord_step();

	time_t timer;
	time(&timer);

	noiser = new NoiseGenerator(timer);
}

ChunkManager::~ChunkManager() 
{
	delete noiser;
}

void ChunkManager::build_block(Chunk* chunk)
{
	_current_chunk = chunk;
	Block* blocks = _current_chunk->get_block_ptr();
	GLuint* height_map = _current_chunk->get_height_map();
	build_height_map(height_map);
	GLuint x, y, z;
	for (y = 0; y < CHUNK_WIDTH_SIZE; ++y)
		for (z = 0; z < CHUNK_WIDTH_SIZE; ++z)
			for (x = 0; x < CHUNK_WIDTH_SIZE; ++x) 
			{
				GLuint height = height_map[x + CHUNK_WIDTH_SIZE * z] % CHUNK_WIDTH_SIZE;
				int idx = y * CHUNK_LAYER_SIZE + z * CHUNK_WIDTH_SIZE + x;
				if (y > height) blocks[idx] = BlockType::AIR;
				else blocks[idx] = BlockType::DIRT;
			}
}

void ChunkManager::build_height_map(GLuint* height_map)
{


	int i, j;
	for (j = 0; j < CHUNK_WIDTH_SIZE; ++j)
		for (i = 0; i < CHUNK_WIDTH_SIZE; ++i)
		{
			height_map[i + CHUNK_WIDTH_SIZE * j] = noiser->getHeight(i, j,
				_current_chunk->get_posX(), _current_chunk->get_posZ());
		}
}

void ChunkManager::build_mesh(Chunk* chunk)
{
	_current_chunk = chunk;
	_current_chunk->clear_mesh();
	_current_indice = 0;
	GLint world_posX = _current_chunk->get_posX();
	GLint world_posZ = _current_chunk->get_posZ();

	_mesh = _current_chunk->get_mesh();
	Block* blocks = _current_chunk->get_block_ptr();
	//_coord = Block::block_manager.get_tex_coord(World::get_block_type(_posX, _posY, _posZ));

	_coord = Block::block_manager.get_tex_coord(BlockType::DIRT);

	for (_posY = 0; _posY < CHUNK_WIDTH_SIZE; ++_posY)
	{
		for (_posZ = world_posZ * CHUNK_WIDTH_SIZE; _posZ < world_posZ * CHUNK_WIDTH_SIZE + CHUNK_WIDTH_SIZE; ++_posZ)
		{
			for (_posX = world_posX * CHUNK_WIDTH_SIZE; _posX < world_posX * CHUNK_WIDTH_SIZE + CHUNK_WIDTH_SIZE; ++_posX)
			{
				GLint lx = _posX - world_posX * CHUNK_WIDTH_SIZE;
				GLint lz = _posZ - world_posZ * CHUNK_WIDTH_SIZE;
				if (blocks[_posY * CHUNK_LAYER_SIZE + lz * CHUNK_WIDTH_SIZE + lx].get_type() == BlockType::AIR) continue;
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

	GLfloat x = (GLfloat)_posX;
	GLfloat y = (GLfloat)_posY;
	GLfloat z = (GLfloat)_posZ;
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
#if 0
	auto type = World::get_block_type(pos[0], pos[1], pos[2]);
#else
	auto type = _current_chunk->get_block_type_within_chunk(pos[0], pos[1], pos[2]);
#endif	
	if (type != BlockType::AIR)
	{
		return false;
	}
	return true;
}
