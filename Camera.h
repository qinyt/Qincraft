#pragma once
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"Entity.h"
#include"Frustum.h"

class Camera 
{
public:
	Camera();
	~Camera();
	void update();
	inline void hook_entity(Entity* entity)		{ _p_entity = entity; }
	//inline glm::mat4x4* get_model_view_mat()	{ return &_model_view_mat; }
	inline glm::mat4x4* get_proj_view_mat()	{ return &_proj_view_mat; }
	inline glm::mat4x4* get_sky_view_mat() { return &_sky_view_mat; }
	glm::mat4x4& get_proj_mat();
	ViewFrustum* get_view_frustum();
private:
	glm::mat4x4	_model_view_mat;
	glm::mat4x4	_proj_mat;
	glm::mat4x4 _proj_view_mat;
	glm::mat4x4 _sky_view_mat;
	Entity* _p_entity;
	ViewFrustum _frustum;
};