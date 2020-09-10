#pragma once
#include<glm/glm.hpp>
#include<glm/ext.hpp>

class Entity
{
public:
	Entity() = default;
	virtual ~Entity() = default;
	virtual void update() = 0;
	virtual void render() = 0;
	inline glm::vec3* get_position() { return &_position; }
	inline glm::vec3* get_rotation() { return &_rotation; }

public:
	glm::vec3 _position, _rotation;
};