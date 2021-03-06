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
        public:
            enum gameMode
                {
                    E_V_E,
                    NEVER_ENDING_E_V_E,

                    P_V_E,
                    NEVER_ENDING_P_V_E,

                    P_V_P,
                    NEVER_ENDING_P_V_P
                };

        private:
            paddle *_home;
            paddle *_away;

            scoreManager _scoreManager;
            ball *_ball;

            countdown _endGameCountdown;

            sf::Text _gameOverText;

            sf::Vector2f _goalLeft;
            sf::Vector2f _goalRight;

            sf::Vector2u _windowSize;

            bool _gameOver;
            bool _neverEnding;

            const int _maxScore;

            gameMode _currentMode;

        public:
            gameState() = default;
            gameState(const int maxScore, gameMode mode);

            void initialize();

            void setGameMode(gameMode mode);
            
            void render();
            void update(sf::Time deltaTime);
            
            void cleanup();
            ~gameState();
    };