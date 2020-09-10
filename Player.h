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
	inline glm::vec3* get_direction() { return &_direction; }
private:
	void handle_input();
	float _speed;	
	glm::vec3 _direction, _acceleration;
};