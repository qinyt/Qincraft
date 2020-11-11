#include"Camera.h"
#include"print_util.h"
#include"Player.h"

Camera::Camera():
	_p_entity(0), 
	_model_view_mat(glm::mat4x4(1.0f)),
	_proj_mat(glm::perspective(glm::radians(30.0f), 1.5f, 0.1f, 1000.0f))
{
}

Camera::~Camera() {}

glm::mat4x4& Camera::get_proj_mat() 
{ return _proj_mat; }

ViewFrustum* Camera::get_view_frustum()
{
	return &_frustum;
}

void Camera::update() 
{
	auto p_pos = _p_entity->get_position();
	auto dir = ((Player*)_p_entity)->get_forward_dir();
	*dir += *p_pos;
	auto up = ((Player*)_p_entity)->get_up_dir();
	_model_view_mat = std::move(glm::lookAt(*p_pos, *dir, *up));
	_sky_view_mat = _model_view_mat;
	_sky_view_mat[3][0] = 0.0f;
	_sky_view_mat[3][1] = 0.0f;
	_sky_view_mat[3][2] = 0.0f;
	_proj_view_mat = _proj_mat * _model_view_mat;
	_frustum.update(_proj_view_mat);
}

