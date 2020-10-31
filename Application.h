#pragma once

#include<SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include"Keyboard.h"
#include"Game.h"
#include"Timer.h"

#define WIN_WIDTH	1500
#define WIN_HEIGHT	1000

#define SHOW_TRI_COUNT 0

class App 
{
public:
	App();
	~App();
	void loop();
	void init();

private:
	void poll_event();
	void init_win();
	Game* _game;
	Timer _timer;
public:
	static Keyboard keyboard;
	static sf::Window window;
	static bool is_running;
#if SHOW_TRI_COUNT 
	static int tri_count;
#endif
};