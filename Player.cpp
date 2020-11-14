#include"Application.h"
#include"Player.h"
#include<cmath>
#include"print_util.h"
#include"World.h"

#define DEBUG 1

#define DEGREE_TO_RADIAN  3.1415926f/180.0f

Player::Player():
	_speed(0.01f),
	_head(0.0f * DEGREE_TO_RADIAN),
	_pitch(80.0f)
{
	_position = glm::vec3(16530, 73, 16055);
	_dir_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

Player::~Player() {}

void Player::update() 
{
	handle_mouse();
	handle_input();
	_position += _acceleration;
	_acceleration *= 0.95f;
}

void Player::handle_mouse() 
{
	glm::mat3  rotHead, rotPitch, rot_mat;

	static float const BOUND = 89.f;
	static auto lastMousePosition = sf::Mouse::getPosition(App::window);
	sf::Vector2i change = sf::Mouse::getPosition(App::window) - lastMousePosition;

	_head  += change.x * 0.01f;
	_pitch += change.y * 0.01f;

	if (_pitch > BOUND * DEGREE_TO_RADIAN)
		_pitch = BOUND * DEGREE_TO_RADIAN;
	else if (_pitch < -BOUND * DEGREE_TO_RADIAN)
		_pitch = -BOUND * DEGREE_TO_RADIAN;

	if (_head > 180.0f * DEGREE_TO_RADIAN)
		_head = -180.0f * DEGREE_TO_RADIAN;
	else if (_head < -180.0f * DEGREE_TO_RADIAN)
		_head = 180.0f * DEGREE_TO_RADIAN;


	//Rotation head (y)
	rotHead[0][0] = cos(_head);			rotHead[0][1] = 0;			rotHead[0][2] = sin(_head);
	rotHead[1][0] = 0;					rotHead[1][1] = 1;			rotHead[1][2] = 0;
	rotHead[2][0] = -sin(_head);		rotHead[2][1] = 0;			rotHead[2][2] = cos(_head);

	//Rotation pitch (x)
	rotPitch[0][0] = 1;		rotPitch[0][1] = 0;					rotPitch[0][2] = 0;
	rotPitch[1][0] = 0;		rotPitch[1][1] = cos(_pitch);		rotPitch[1][2] = -sin(_pitch);
	rotPitch[2][0] = 0;		rotPitch[2][1] = sin(_pitch);		rotPitch[2][2] =  cos(_pitch);

	rot_mat = std::move( rotHead * rotPitch);

	_dir_forward	= rot_mat * glm::vec3(0.0f, 0.0f, -1.0f);
	_dir_right		= rot_mat * glm::vec3(1.0f, 0.0f,  0.0f);
	_dir_up			= rot_mat * glm::vec3(0.0f, 1.0f,  0.0f);

	auto cx = static_cast<int>(App::window.getSize().x / 2);
	auto cy = static_cast<int>(App::window.getSize().y / 2);

	sf::Mouse::setPosition({ cx, cy }, App::window);

	lastMousePosition = sf::Mouse::getPosition(App::window);
}

void Player::handle_input() 
{
	//keyboard
	auto* key = &App::keyboard;
	if (key->is_key_down(sf::Keyboard::Key::W))
	{
		float s = _speed;	
		if (key->is_key_down(sf::Keyboard::Key::LShift))
			s *= 5.0f;
		_acceleration += _dir_forward * s;
	}
	if (key->is_key_down(sf::Keyboard::Key::S))
	{
		_acceleration -= _dir_forward * _speed;
	}																   
	if (key->is_key_down(sf::Keyboard::Key::A))						   
	{											
		_acceleration -= _dir_right * _speed;
	}
	if (key->is_key_down(sf::Keyboard::Key::D))
	{
		_acceleration += _dir_right * _speed;
	}
#if DEBUG
	if (App::keyboard.is_key_down(sf::Keyboard::Key::Enter))
	{
		printf("position:%f, %f, %f\n",_position.x, _position.y, _position.z);
		__debugbreak();
	}
#endif
}

void Player::render() 
{

}

void Player::set_y_pos(float y) { _position.y = y; }

void Player::slect_block()
{
	auto pos = _position;
	while (1) 
	{
		pos += _dir_forward * 5.0f;
		auto ty = World::get_block_type(pos.x, pos.y, pos.z);
		if (ty != BlockType::AIR) __debugbreak();				
	}
}



