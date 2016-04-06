#include "player.hpp"
#include "../game/globals.hpp"

bool player::_secondPlayer = false;

player::player(float maxHeight, float minHeight, sf::Vector2f startPos) : paddle(maxHeight, minHeight, startPos)
    {
        if (!_secondPlayer)
            {
                globals::_keyboardManager.add(sf::Keyboard::W, [this] () { _impulse.y = -_speed; }, true, GAME_STATE);
                globals::_keyboardManager.add(sf::Keyboard::W, [this] () { _impulse.y = 0.0f; }, false, GAME_STATE);

                globals::_keyboardManager.add(sf::Keyboard::S, [this] () { _impulse.y = _speed; }, true, GAME_STATE);
                globals::_keyboardManager.add(sf::Keyboard::S, [this] () { _impulse.y = 0.0f; }, false, GAME_STATE);
            }
        else // very hacky way last-minute way to implement a second player
            {
                globals::_keyboardManager.add(sf::Keyboard::Up, [this] () { _impulse.y = -_speed; }, true, GAME_STATE);
                globals::_keyboardManager.add(sf::Keyboard::Up, [this] () { _impulse.y = 0.0f; }, false, GAME_STATE);

                globals::_keyboardManager.add(sf::Keyboard::Down, [this] () { _impulse.y = _speed; }, true, GAME_STATE);
                globals::_keyboardManager.add(sf::Keyboard::Down, [this] () { _impulse.y = 0.0f; }, false, GAME_STATE);
            }

        _secondPlayer = true;
    }

player::~player()
    {
        _secondPlayer = false;
    }
