#pragma once
#include"SimpleRenderer.h"
#include "Player.h"
#include "Camera.h"
#include"ChunkRenderer.h"
#include"SkyRenderer.h"

class Game 
{
public: 
	Game();
	~Game();
	void update();
	void render();
private:
	SimpleRenderer  _simple_renderer;
	ChunkRenderer   _chunk_renderer;
	SkyRenderer		_sky_renderer;
	Player _player;
	Camera _camera;
};