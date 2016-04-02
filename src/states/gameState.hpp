// gameState.hpp
// the game state. Handles the PVE game world
#pragma once

#include "state.hpp"
#include "../managers/score/scoreManager.hpp"
#include "../utilities/countdown.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>

class ball;
class paddle;
class player;
class aiPaddle;

class gameState : public state
    {
        private:
            player *_player;
            aiPaddle *_opponent;

        protected:
            scoreManager _scoreManager;
            ball *_ball;

            countdown _endGameCountdown;

            sf::Text _gameOverText;

            sf::Vector2f _goalLeft;
            sf::Vector2f _goalRight;

            bool _gameOver;
            const int _maxScore;

        public:
            gameState() = default;
            gameState(sf::Vector2u windowSize, const int maxScore);
            
            void render(sf::RenderWindow &app);
            void update(sf::Time deltaTime);
            
            ~gameState();
    };