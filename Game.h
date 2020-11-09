#pragma once
//#include"SimpleRenderer.h"
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
	static Player	player;
private:
	Camera _camera;
	World	_world;
	SkyRenderer		_sky_renderer;
	//SimpleRenderer	_simpleRenderer;
	ChunkRenderer   _chunk_renderer;
};