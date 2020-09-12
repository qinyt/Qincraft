#include"Camera.h"
#include"print_util.h"
#include"Player.h"

Camera::Camera():
	_p_entity(0), 
	_model_view_mat(glm::mat4x4(1.0f))
{

}

Camera::~Camera() {}



void Camera::update() 
{
	auto p_pos = _p_entity->get_position();
	auto dir = ((Player*)_p_entity)->get_forward_dir();
	*dir += *p_pos;
	auto up = ((Player*)_p_entity)->get_up_dir();

	_model_view_mat = std::move(glm::lookAt(*p_pos, *dir, *up));
}

