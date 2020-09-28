#pragma once
#include"SimpleRenderer.h"
#include "Player.h"
#include "Camera.h"
#include"ChunkRenderer.h"
#include"SkyRenderer.h"
#include"World.h"


class Game 
{
public: 
	Game();
	~Game();
	void update();
	void render();
private:
	World	_world;
	Player _player;
	Camera _camera;
	//SkyRenderer		_sky_renderer;
	ChunkRenderer   _chunk_renderer;
};