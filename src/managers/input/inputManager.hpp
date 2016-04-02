// inputManager.hpp
// manges all inputs in the game.
#pragma once

#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include "input.hpp"

class inputManager
    {
        private:
            // all inputs that are mapped. Has the input ID and the input
            std::unordered_map<std::string, input> _inputs;

        public:
            void handleInput(sf::Keyboard::Key key);
            void map(const std::string &name, sf::Keyboard::Key key, std::function<void()> functionOnActive);
    };