#include "gameState.hpp"

#include "../entity/paddle.hpp"
#include "../entity/aiPaddle.hpp"
#include "../entity/ball.hpp"
#include "../entity/player.hpp"

#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

gameState::gameState(sf::Vector2u windowSize, const int maxScore, gameState::gameMode mode) : _maxScore(maxScore)
    {
        const int distanceFromWall = 30;
        _state = GAME_STATE;
        _currentMode = mode;


        _ball = new ball(windowSize);

        switch (_currentMode)
            {
                case gameState::E_V_E:
                    _home = new aiPaddle(windowSize.y, 0, sf::Vector2f(distanceFromWall, windowSize.y / 2), _ball, aiPaddle::MEDIUM);
                    _away = new aiPaddle(windowSize.y, 0, sf::Vector2f((windowSize.x - distanceFromWall), windowSize.y / 2), _ball, aiPaddle::HARD);
                    break;
                case gameState::P_V_E:
                    _home = new player(windowSize.y, 0, sf::Vector2f(distanceFromWall, windowSize.y / 2));
                    _away = new aiPaddle(windowSize.y, 0, sf::Vector2f((windowSize.x - distanceFromWall), windowSize.y / 2), _ball, aiPaddle::MEDIUM);
                    break;
                case gameState::P_V_P:
                    _home = new player(windowSize.y, 0, sf::Vector2f(distanceFromWall, windowSize.y / 2));
                    _away = new player(windowSize.y, 0, sf::Vector2f((windowSize.x - distanceFromWall), windowSize.y / 2));
                    break;
                default:
                    break;
            }
        

        _goalLeft = sf::Vector2f(0, 0);
        _goalRight = sf::Vector2f(windowSize.x, windowSize.y);

        _scoreManager.addNewScore("leftGoal", sf::Vector2f((windowSize.x / 2) - 60, 30));
        _scoreManager.getScore("leftGoal")->getText().setCharacterSize(64);

        _scoreManager.addNewScore("rightGoal", sf::Vector2f((windowSize.x / 2) + 60, 30));
        _scoreManager.getScore("rightGoal")->getText().setCharacterSize(64);

        _gameOverText.setFont(*globals::_fontManager.get("gameFont"));
        _gameOverText.setCharacterSize(70);
        _gameOverText.setPosition(windowSize.x / 2, windowSize.y / 2);
    }

void gameState::render(sf::RenderWindow &app)
    {
        _home->draw(app);
        _away->draw(app);
        _ball->draw(app);
        _scoreManager.render(app);

        if (_gameOver)
            {
                app.draw(_gameOverText);
            }
    }

void gameState::update(sf::Time deltaTime)
    {
        if (!_gameOver)
            {
                _home->update(deltaTime);

                //_away->updateBallPos(_ball->getPosition(), _ball->getImpulse(), deltaTime);
                _away->update(deltaTime);

                _ball->collide(*_home->getSprite());
                _ball->collide(*_away->getSprite());
                _ball->update(deltaTime);
            }

        if ((_ball->getPosition().x < _goalLeft.x || _ball->getPosition().x > _goalRight.x) && !_gameOver)
            {
                if (_ball->getPosition().x > _goalRight.x)
                    {
                        _scoreManager.incrementScore("leftGoal");
                        if (_scoreManager.getScore("leftGoal")->getScore() >= _maxScore)
                            {
                                _gameOverText.setString("Left Wins!");
                                _gameOver = true;
                                _endGameCountdown.start(sf::seconds(3));

                                _gameOverText.setPosition(_gameOverText.getPosition().x - (_gameOverText.getLocalBounds().width / 2),
                                                          _gameOverText.getPosition().y - (_gameOverText.getLocalBounds().height / 2));
                            }
                    }
                else
                    {
                        _scoreManager.incrementScore("rightGoal");
                        if (_scoreManager.getScore("rightGoal")->getScore() >= _maxScore)
                            {
                                _gameOverText.setString("Right Wins!");
                                _gameOver = true;
                                _endGameCountdown.start(sf::seconds(3));

                                _gameOverText.setPosition(_gameOverText.getPosition().x - (_gameOverText.getLocalBounds().width / 2),
                                                          _gameOverText.getPosition().y - (_gameOverText.getLocalBounds().height / 2));
                            }
                    }

                if (!_gameOver)
                    {
                        _ball->initialize();
                        _home->initialize();
                        _away->initialize();
                    }
            }

        if (_endGameCountdown.hasCountdownFinished() && _gameOver)
            {
                globals::_stateMachine.popState();
            }
    }

gameState::~gameState()
    {
        delete _home;
        delete _away;
        delete _ball;

        _home = nullptr;
        _away = nullptr;
        _ball = nullptr;
    }
