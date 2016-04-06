#include "player.hpp"
#include "../game/globals.hpp"

player::player(float maxHeight, float minHeight, sf::Vector2f startPos) : paddle(maxHeight, minHeight, startPos)
    {
        globals::_keyboardManager.add(sf::Keyboard::Up, [this] () { _impulse.y = -_speed; }, true, GAME_STATE);
        globals::_keyboardManager.add(sf::Keyboard::Up, [this] () { _impulse.y = 0.0f; }, false, GAME_STATE);

        globals::_keyboardManager.add(sf::Keyboard::Down, [this] () { _impulse.y = _speed; }, true, GAME_STATE);
        globals::_keyboardManager.add(sf::Keyboard::Down, [this] () { _impulse.y = 0.0f; }, false, GAME_STATE);
    }