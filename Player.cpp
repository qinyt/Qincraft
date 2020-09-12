#include"Application.h"
#include"Player.h"
#include<cmath>
#include"print_util.h"


Player::Player():
	_speed(0.2f),
	_head(0.0f),
	_pitch(0.0f)
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
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

void mat3x3_mul(const float* m1, const float *m2, float* dest) 
{
	int i;
	int row = 0;
	int colum = 0;
	for (i = 0; i < 9; i++)
	{
		colum = (i / 3) * 3;
		row = i % 3;

		dest[i] = m1[row] * m2[colum] + m1[row + 3] * m2[colum + 1] + m1[row + 6] * m2[colum + 2];
	}
}

void matrix_transform_vec3t(const float* m1, glm::vec3* vect, glm::vec3* dest)
{
	dest[0] = m1[0] * vect[0] + m1[3] * vect[1] + m1[6] * vect[2];
	dest[1] = m1[1] * vect[0] + m1[4] * vect[1] + m1[7] * vect[2];
	dest[2] = m1[2] * vect[0] + m1[5] * vect[1] + m1[8] * vect[2];
}


void Player::handle_mouse() 
{
	glm::mat3  rotHead, rotPitch, rot_mat;

	static float const BOUND = 89.f;
	static auto lastMousePosition = sf::Mouse::getPosition(App::window);
	sf::Vector2i change = sf::Mouse::getPosition(App::window) - lastMousePosition;

	_head  += change.x * 0.01f;
	_pitch += change.y * 0.01f;

	if (_pitch > BOUND)
		_pitch = BOUND;
	else if (_pitch < -BOUND)
		_pitch = -BOUND;

	if (_head > 180.0f)
		_head = 180.0f;
	else if (_head < -180.0f)
		_head = 180.0f;

	//Rotation head (y)
	rotHead[0][0] = cos(_head);			rotHead[0][1] = 0;			rotHead[0][2] = sin(_head);
	rotHead[1][0] = 0;					rotHead[1][1] = 1;			rotHead[1][2] = 0;
	rotHead[2][0] = -sin(_head);		rotHead[2][1] = 0;			rotHead[2][2] = cos(_head);


	//Rotation pitch (x)
	rotPitch[0][0] = 1;		rotPitch[0][1] = 0;					rotPitch[0][2] = 0;
	rotPitch[1][0] = 0;		rotPitch[1][1] = cos(_pitch);		rotPitch[1][2] = -sin(_pitch);
	rotPitch[2][0] = 0;		rotPitch[2][1] = sin(_pitch);		rotPitch[2][2] =  cos(_pitch);


	//glm::mat3x3 rot_mat = std::move(rotHead * rotPitch);
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
#if 1
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
#endif
}


void Player::render() {}
