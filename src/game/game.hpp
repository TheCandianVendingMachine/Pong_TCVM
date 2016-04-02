// game.hpp
// game loop
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../states/stateMachine.hpp"

class game
    {
        private:
            stateMachine _stateMachine;

            void handleInput(sf::RenderWindow &app);

            void initializeResources();

        public:
            void start();
    };