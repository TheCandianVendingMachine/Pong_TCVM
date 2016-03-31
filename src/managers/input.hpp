// input.hpp
// what defines an input. inputManager handles this
#pragma once

#include <functional>
#include <SFML/Window/Keyboard.hpp>

class input
    {
        private:
            std::function<void()> _onKeyPress;
            sf::Keyboard::Key _key;

        public:
            input() = default;
            input(sf::Keyboard::Key key, std::function<void()> function);
            void handle();

            const sf::Keyboard::Key getKey() const;
    };