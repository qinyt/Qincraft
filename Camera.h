#pragma once
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"Entity.h"

class Camera 
{
public:
	Camera();
	~Camera();
	void update();
	inline void hook_entity(Entity* entity)		{ _p_entity = entity; }
	inline glm::mat4x4* get_model_view_mat()	{ return &_model_view_mat; }
private:
	glm::mat4x4	_model_view_mat;
	Entity* _p_entity;
};