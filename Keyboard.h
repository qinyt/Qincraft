#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class Keyboard 
{
public:
	Keyboard() ;
	~Keyboard() = default;
	void update(sf::Event& e);
	bool is_key_down(sf::Keyboard::Key key) const;
private:
	bool _keys[sf::Keyboard::KeyCount];
};