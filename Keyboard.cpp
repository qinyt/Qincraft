#include"Keyboard.h"

Keyboard::Keyboard() 
{
    memset(_keys, 0, sizeof(bool) * sf::Keyboard::KeyCount);
}

void Keyboard::update(sf::Event& e) 
{
    switch (e.type) {
    case sf::Event::KeyReleased:
        _keys[e.key.code] = false;
        break;

    case sf::Event::KeyPressed:
        _keys[e.key.code] = true;
        break;

    default:
        break;
    }
}

bool Keyboard::is_key_down(sf::Keyboard::Key key) const
{
    return _keys[key];
}