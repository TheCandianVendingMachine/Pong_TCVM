#include "player.hpp"
#include "../game/globals.hpp"

player::player(float maxHeight, float minHeight, sf::Vector2f startPos) : paddle(maxHeight, minHeight, startPos)
    {
        mapKeys(sf::Keyboard::Up, sf::Keyboard::Down);
    }

void player::mapKeys(sf::Keyboard::Key up, sf::Keyboard::Key down)
    {
        globals::_inputManager.map("playerUp", up, [this] () { _impulse.y = -_speed; });
        globals::_inputManager.map("playerDown", down, [this] () { _impulse.y = _speed; });
    }