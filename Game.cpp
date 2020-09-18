#include"Game.h"
#include"glad\glad.h"

Game::Game() 
{
	_camera.hook_entity(&_player);
}

Game::~Game()	
{

}

void Game::update() 
{
	_player.update();
	_camera.update();
}

void Game::render() 
{
	glClearColor(0.8f, 0.7f, 0.8f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	_simple_renderer.render(&_camera);
	_chunk_renderer.render(&_camera);
	_sky_renderer.render(&_camera);
}