// gameState.hpp
// the game state. Handles the game world
#pragma once

#include "state.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class ball;
class player;
class aiPaddle;

class gameState : public state
    {
        private:
            player *_player;
            aiPaddle *_opponent;

        protected:
            ball *_ball;

            sf::Vector2f _goalLeft;
            sf::Vector2f _goalRight;

        public:
            gameState() = default;
            gameState(sf::Vector2u windowSize);
            
            void render(sf::RenderWindow &app);
            void update(sf::Time deltaTime);
            
            ~gameState();
    };