#include"Application.h"
#include"Player.h"
#include<cmath>
#include"print_util.h"


Player::Player():_speed(0.2f)
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}


Player::~Player() {}

void Player::update() 
{
	handle_input();
	_position += _acceleration;
	_acceleration *= 0.95f;
}

void Player::handle_input() 
{
	//
	float cosY		= glm::cos(glm::radians(_rotation.y));
	float sinY		= glm::sin(glm::radians(_rotation.y));
	float sinX		= glm::sin(glm::radians(_rotation.x));
	float cosY_90	= glm::cos(glm::radians(_rotation.y + 90.0f));
	float sinY_90	= glm::sin(glm::radians(_rotation.y + 90.0f));

	//keyboard
	auto* key = &App::keyboard;
	if (key->is_key_down(sf::Keyboard::Key::W))
	{
		float s = _speed;	
		if (key->is_key_down(sf::Keyboard::Key::LShift))
			s *= 5.0f;
		_acceleration.x -= cosY_90 * s;
		_acceleration.z -= sinY_90 * s;
	}
	if (key->is_key_down(sf::Keyboard::Key::S))
	{
		_acceleration.x += cosY_90 * _speed;
		_acceleration.z += sinY_90 * _speed;
	}																   
	if (key->is_key_down(sf::Keyboard::Key::A))						   
	{																   
		_acceleration.x -= cosY* _speed;
		_acceleration.z -= sinY* _speed;
	}
	if (key->is_key_down(sf::Keyboard::Key::D))
	{
		_acceleration.x += cosY* _speed;
		_acceleration.z += sinY* _speed;
	}
	//mouse
	static float const BOUND = 89.f;
	static auto lastMousePosition = sf::Mouse::getPosition(App::window);
	sf::Vector2i change = sf::Mouse::getPosition(App::window) - lastMousePosition;
	_rotation.y += change.x * 0.05f;
	_rotation.x += change.y * 0.05f;

	if (_rotation.x > BOUND)
		_rotation.x = BOUND;
	else if (_rotation.x < -BOUND)
		_rotation.x = -BOUND;

	if (_rotation.y > 360)
		_rotation.y = 0;
	else if (_rotation.y < 0)
		_rotation.y = 360;

	_direction.z = -sinY_90;
	_direction.x = -cosY_90;
	_direction.y = -sinX;

	auto cx = static_cast<int>(App::window.getSize().x / 2);
	auto cy = static_cast<int>(App::window.getSize().y / 2);

	sf::Mouse::setPosition({ cx, cy }, App::window);

	lastMousePosition = sf::Mouse::getPosition(App::window);
}


void Player::render() {}
