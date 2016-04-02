#include "gameState.hpp"

#include "../entity/paddle.hpp"
#include "../entity/aiPaddle.hpp"
#include "../entity/ball.hpp"
#include "../entity/player.hpp"

gameState::gameState(sf::Vector2u windowSize)
    {
        const int distanceFromWall = 30;
        _state = PLAYER_AI_GAME_STATE;

        _player = new player(windowSize.y, 0, sf::Vector2f(distanceFromWall, windowSize.y / 2));
        _opponent = new aiPaddle(windowSize.y, 0, sf::Vector2f((windowSize.x - distanceFromWall), windowSize.y / 2));
        _ball = new ball(windowSize);

        _goalLeft = sf::Vector2f(0, 0);
        _goalRight = sf::Vector2f(windowSize.x, windowSize.y);

        _scoreManager.addNewScore("leftGoal", sf::Vector2f((windowSize.x / 2) - 60, 30));
        _scoreManager.getScore("leftGoal")->getText().setCharacterSize(64);

        _scoreManager.addNewScore("rightGoal", sf::Vector2f((windowSize.x / 2) + 60, 30));
        _scoreManager.getScore("rightGoal")->getText().setCharacterSize(64);
    }

void gameState::render(sf::RenderWindow &app)
    {
        _player->draw(app);
        _opponent->draw(app);
        _ball->draw(app);
        _scoreManager.render(app);
    }

void gameState::update(sf::Time deltaTime)
    {
        _player->update(deltaTime);

        _opponent->updateBallPos(_ball->getPosition(), _ball->getImpulse(), deltaTime);
        _opponent->update(deltaTime);

        _ball->collide(*_player->getSprite());
        _ball->collide(*_opponent->getSprite());
        _ball->update(deltaTime);

        if (_ball->getPosition().x < _goalLeft.x || _ball->getPosition().x > _goalRight.x)
            {
                _ball->initialize();
                _player->initialize();
                _opponent->initialize();

                if (_ball->getPosition().x < _goalLeft.x)
                    {
                        _scoreManager.incrementScore("leftGoal");
                        if (_scoreManager.getScore("leftGoal")->getScore() >= 10)
                            {
                                
                            }
                    }
                else
                    {
                        _scoreManager.incrementScore("rightGoal");
                        if (_scoreManager.getScore("rightGoal")->getScore() >= 10)
                            {
                                
                            }
                    }
            }
    }

gameState::~gameState()
    {
        delete _player;
        delete _opponent;
        delete _ball;

        _player = nullptr;
        _opponent = nullptr;
        _ball = nullptr;
    }
