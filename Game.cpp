#include"Game.h"
#include"glad\glad.h"

Player Game::player;

Game::Game() 
{
	_camera.hook_entity(&player);
	_world.set_chunk_renderer(&_chunk_renderer);
}

Game::~Game()	
{

}

void Game::update() 
{
	player.update();
	_camera.update();
	_world.update();
}

void Game::render() 
{
	glClearColor(0.8f, 0.7f, 0.8f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	_world.render();
	//_simpleRenderer.render(&_camera);
	_chunk_renderer.render(&_camera);
	_sky_renderer.render(&_camera);
}