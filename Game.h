#pragma once
#include"SimpleRenderer.h"
#include "Player.h"
#include "Camera.h"

class Game 
{
public: 
	Game();
	~Game();
	void update();
	void render();
private:
	SimpleRenderer _simple_renderer;
	Player _player;
	Camera _camera;
};