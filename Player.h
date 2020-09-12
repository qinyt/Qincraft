#pragma once

#include"Entity.h"
//#include"Application.h"

class App;
class Player: public Entity 
{
public:
	Player();
	~Player();
	void render() override;
	void update() override;
	inline glm::vec3* get_forward_dir() { return &_dir_forward; }
	inline glm::vec3* get_up_dir() { return &_dir_up; }
private:
	void handle_input();
	void handle_mouse();
	float _speed, _pitch, _head;	
	glm::vec3 _dir_forward, _dir_right, _dir_up, _acceleration;
};