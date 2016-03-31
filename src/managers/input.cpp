#include "input.hpp"

input::input(sf::Keyboard::Key key, std::function<void()> function)
    {
        _key = key;
        _onKeyPress = function;
    }

void input::handle()
    {
        _onKeyPress();
    }

const sf::Keyboard::Key input::getKey() const
    {
        return _key;
    }
