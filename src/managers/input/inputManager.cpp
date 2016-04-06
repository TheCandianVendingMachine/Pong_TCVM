#include "inputManager.hpp"

void inputManager::add(sf::Keyboard::Key key, std::function<void()> onInput, bool onPress, states activeState)
    {
        _inputs.emplace_back(key, onInput, onPress, activeState);
    }

void inputManager::handleInput(sf::Event &event, states currentState)
    {
        for (auto &key : _inputs)
            {
                key.execute(event, currentState);
            }
    }
