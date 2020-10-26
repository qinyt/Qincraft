#include"Chunk.h"
#include"Math.h"
#include"World.h"
#include<memory>
#include"ChunkManager.h"
#include"Random.h"

#define ADD_INDICE GLuint index[6]; \
index[0] = _current_indice + 0; \
index[1] = _current_indice + 1; \
index[2] = _current_indice + 3; \
index[3] = _current_indice + 1; \
index[4] = _current_indice + 2; \
index[5] = _current_indice + 3; \
for (int i = 0; i < 6; ++i) _mesh->add_index(index[i]); \
_current_indice += 4

namespace {
	const int seed = RandomSingleton::get().intInRange(424, 325322);
}
static int current_height_map[CHUNK_LAYER_SIZE];
static int current_biome_map[CHUNK_LAYER_SIZE];
static int cur_max_height, cur_min_height;

#define likely(x)  __builtin_expect(!!(x), 1)

static Adjacency_t adj;

ChunkManager::ChunkManager()
	: m_grassBiome(seed)
	, m_temperateForest(seed)
	, m_desertBiome(seed)
	, m_oceanBiome(seed)
	, m_lightForest(seed)
	, noiser(seed)
{
	_tex_step = Block::block_manager.get_tex_coord_step();
}

ChunkManager::~ChunkManager() {}

void ChunkManager::build_cylinder(ChunkCylinder* cy) 
{
	_cur_chunk_cylinder = cy;
	build_biome_map();
	build_height_map();
	get_max_min_height();
	_cur_chunk_cylinder->set_max_height(cur_max_height);
	_cur_chunk_cylinder->set_min_height(cur_min_height);
	_cur_chunk_cylinder->add_chunk();
	build_block();
}

void ChunkManager::build_block()
{
	int x, y, z;
	for (auto& chunk : _cur_chunk_cylinder->get_chunks()) 
	{
		Block* blocks = chunk.get_block_ptr();
		int baseY = chunk.get_pos().y * CHUNK_WIDTH_SIZE;
		int delta = ((cur_max_height - baseY * CHUNK_WIDTH_SIZE) < CHUNK_WIDTH_SIZE) ?
					cur_max_height : baseY + CHUNK_WIDTH_SIZE;
		for (y = baseY; y < delta; ++y)
		for (z = 0; z < CHUNK_WIDTH_SIZE; ++z)
		for (x = 0; x < CHUNK_WIDTH_SIZE; ++x) 
		{
			int deltaY = y % CHUNK_WIDTH_SIZE;
			int idx = deltaY * CHUNK_LAYER_SIZE + z * CHUNK_WIDTH_SIZE + x;
			int height = current_height_map[x + CHUNK_WIDTH_SIZE * z];
			if (y > height) blocks[idx] = BlockType::AIR;
			else blocks[idx] = BlockType::DIRT_TOP;
		}
	}
}

void ChunkManager::build_biome_map()
{
	GLint* map = current_biome_map;
	int i, j;
	int x = _cur_chunk_cylinder->get_pos().x;
	int z = _cur_chunk_cylinder->get_pos().z;
	for (j = 0; j < CHUNK_WIDTH_SIZE; ++j)
	for (i = 0; i < CHUNK_WIDTH_SIZE; ++i)
	{
		map[i + CHUNK_WIDTH_SIZE * j] = (int) (noiser.getHeight(i, j, x, z));
	}
}

void ChunkManager::get_max_min_height()
{
	int* map = current_height_map;
	cur_max_height = 0;
	cur_min_height = 99999;
	for (int i = 0; i < CHUNK_WIDTH_SIZE * CHUNK_WIDTH_SIZE; ++i) 
	{
		if (map[i] > cur_max_height) cur_max_height = map[i];
		if (map[i] < cur_min_height) cur_min_height = map[i];
	}
}

void ChunkManager::build_height_map()
{
	int* bio_map = current_biome_map;
	int* map = current_height_map;
	int i, j;
	int x = _cur_chunk_cylinder->get_pos().x;
	int z = _cur_chunk_cylinder->get_pos().z;
	for (j = 0; j < CHUNK_WIDTH_SIZE; ++j)
		for (i = 0; i < CHUNK_WIDTH_SIZE; ++i)
		{
			//TODO: use interpolation to optimize
			int h = (getBiome(i, j, bio_map).getHeight(i, j, x, z));
			map[i + CHUNK_WIDTH_SIZE * j] = h;
		}
}

void ChunkManager::build_mesh(ChunkCylinder* cy)
{
	_cur_chunk_cylinder = cy;
	int max_h = _cur_chunk_cylinder->get_max_height();
	for (auto& chunk : _cur_chunk_cylinder->get_chunks())
	{
		chunk.clear_mesh();
		_current_indice = 0;
		_mesh = chunk.get_mesh();
		Block* blocks = chunk.get_block_ptr();

		auto pos = chunk.get_pos();
		int base = pos.y * CHUNK_WIDTH_SIZE;
		int delta =  max_h % CHUNK_WIDTH_SIZE;
		int lz = pos.z * CHUNK_WIDTH_SIZE;
		int lx = pos.x * CHUNK_WIDTH_SIZE;
		for (_posY = base; _posY < base + delta; ++_posY)
		{
			for (_posZ = lz; _posZ < lz + CHUNK_WIDTH_SIZE; ++_posZ)
			{
				for (_posX = lx; _posX < lx + CHUNK_WIDTH_SIZE; ++_posX)
				{
					int ix = _posX - lx;
					int iz = _posZ - lz;
					int iy = _posY - base;
					auto block_type = blocks[iy * CHUNK_LAYER_SIZE + iz * CHUNK_WIDTH_SIZE + ix].get_type();
					if (block_type == BlockType::AIR) continue;
					_coord = Block::block_manager.get_tex_coord(block_type);
					try_build_front_face();
					try_build_back_face();
					try_build_up_face();
					try_build_left_face();
					try_build_right_face();
				}
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
	int pos[3] = { _posX, _posY, _posZ };
	math::vec3i_add(pos, dir, pos);
	
	BlockType type;
#if 0
	type = World::get_block_type(pos[0], pos[1], pos[2]);
#else
	int a = pos[0] % CHUNK_WIDTH_SIZE;
	int c = pos[2] % CHUNK_WIDTH_SIZE;
	bool inside = !(a == 0 || a == CHUNK_WIDTH_SIZE - 1 || c == 0 || c == CHUNK_WIDTH_SIZE - 1);
	if(inside)
	{
		auto base = _cur_chunk_cylinder->get_pos();
		int ix = pos[0] - base.x * CHUNK_WIDTH_SIZE;
		int iz = pos[2] - base.z * CHUNK_WIDTH_SIZE;
		type = _cur_chunk_cylinder->get_block_within(ix, pos[1], iz);
	}
	else 
	{
		type = World::get_block_type(pos[0], pos[1], pos[2]);
	}
	
#endif
	if (type != BlockType::AIR)
	{
		return false;
	}
	return true;
}


const Biome& ChunkManager::getBiome(int x, int z, GLint* map) const
{
	GLint biomeValue = map[x + CHUNK_WIDTH_SIZE * z];
	return m_grassBiome;
	//if (biomeValue > 160) {
	//	return m_oceanBiome;
	//}
	//else if (biomeValue > 150) {
	//	return m_grassBiome;
	//}
	//else if (biomeValue > 130) {
	//	return m_lightForest;
	//}
	//else if (biomeValue > 120) {
	//	return m_temperateForest;
	//}
	//else if (biomeValue > 110) {
	//	return m_lightForest;
	//}
	//else if (biomeValue > 100) {
	//	return m_grassBiome;
	//}
	//else {
	//	return m_desertBiome;
	//}
}