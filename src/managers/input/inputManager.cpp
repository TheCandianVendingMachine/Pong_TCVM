#include "inputManager.hpp"

void inputManager::handleInput(sf::Keyboard::Key key)
    {
        for (auto &keys : _inputs)
            {
                if (keys.second.getKey() == key)
                    {
                        keys.second.handle();
                    }
            }
    }

void inputManager::map(const std::string &name, sf::Keyboard::Key key, std::function<void()> functionOnActive)
    {
        _inputs[name] = input(key, functionOnActive);
    }
