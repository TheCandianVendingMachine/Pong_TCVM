#include "gameState.hpp"
#include "menuState.hpp"

#include "../entity/paddle.hpp"
#include "../entity/aiPaddle.hpp"
#include "../entity/ball.hpp"
#include "../entity/player.hpp"

#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

gameState::gameState(const int maxScore, gameState::gameMode mode) : _maxScore(maxScore)
    {
        _state = GAME_STATE;
        _currentMode = mode;

        _renderOvertop = false;
        _updateUnderneath = false;
        _isInitialized = false;

        sf::Vector2u windowSize = globals::_stateMachine.getWindow()->getSize();

        _goalLeft = sf::Vector2f(0, 0);
        _goalRight = sf::Vector2f(windowSize.x, windowSize.y);

        _windowSize = windowSize;

        _scoreManager.addNewScore("leftGoal", sf::Vector2f((windowSize.x / 2) - 60, 30));
        _scoreManager.getScore("leftGoal")->getText().setCharacterSize(64);

        _scoreManager.addNewScore("rightGoal", sf::Vector2f((windowSize.x / 2) + 60, 30));
        _scoreManager.getScore("rightGoal")->getText().setCharacterSize(64);

        _gameOverText.setFont(*globals::_fontManager.get("gameFont"));
        _gameOverText.setCharacterSize(70);
        _gameOverText.setPosition(windowSize.x / 2, windowSize.y / 2);

        initialize();
    }

void gameState::initialize()
    {
        const int distanceFromWall = 30;
        _isInitialized = true;

        cleanup();
        _ball = new ball(_windowSize);

        _neverEnding = false;

        switch (_currentMode)
            {
                case gameState::E_V_E:
                    _home = new aiPaddle(_windowSize.y, 0, sf::Vector2f(distanceFromWall, _windowSize.y / 2), _ball, aiPaddle::MEDIUM);
                    _away = new aiPaddle(_windowSize.y, 0, sf::Vector2f((_windowSize.x - distanceFromWall), _windowSize.y / 2), _ball, aiPaddle::HARD);
                    break;
                case gameState::NEVER_ENDING_E_V_E:
                    _home = new aiPaddle(_windowSize.y, 0, sf::Vector2f(distanceFromWall, _windowSize.y / 2), _ball, aiPaddle::MEDIUM);
                    _away = new aiPaddle(_windowSize.y, 0, sf::Vector2f((_windowSize.x - distanceFromWall), _windowSize.y / 2), _ball, aiPaddle::HARD);
                    _neverEnding = true;
                    break;
                ////////////////////////////////////////////////
                case gameState::P_V_E:
                    _home = new player(_windowSize.y, 0, sf::Vector2f(distanceFromWall, _windowSize.y / 2));
                    _away = new aiPaddle(_windowSize.y, 0, sf::Vector2f((_windowSize.x - distanceFromWall), _windowSize.y / 2), _ball, aiPaddle::MEDIUM);
                    break;
                case gameState::NEVER_ENDING_P_V_E:
                    _home = new player(_windowSize.y, 0, sf::Vector2f(distanceFromWall, _windowSize.y / 2));
                    _away = new aiPaddle(_windowSize.y, 0, sf::Vector2f((_windowSize.x - distanceFromWall), _windowSize.y / 2), _ball, aiPaddle::MEDIUM);
                    _neverEnding = true;
                    break;
                ///////////////////////////////////////////////
                case gameState::P_V_P:
                    _home = new player(_windowSize.y, 0, sf::Vector2f(distanceFromWall, _windowSize.y / 2));
                    _away = new player(_windowSize.y, 0, sf::Vector2f((_windowSize.x - distanceFromWall), _windowSize.y / 2));
                    break;
                case gameState::NEVER_ENDING_P_V_P:
                    _home = new player(_windowSize.y, 0, sf::Vector2f(distanceFromWall, _windowSize.y / 2));
                    _away = new player(_windowSize.y, 0, sf::Vector2f((_windowSize.x - distanceFromWall), _windowSize.y / 2));
                    _neverEnding = true;
                    break;
                default:
                    break;
            }

        _scoreManager.resetScore("leftGoal");
        _scoreManager.resetScore("rightGoal");

        _gameOver = false;
    }

void gameState::setGameMode(gameMode mode)
    {
        _currentMode = mode;
    }

void gameState::render()
    {
        _home->draw(*globals::_stateMachine.getWindow());
        _away->draw(*globals::_stateMachine.getWindow());
        _ball->draw(*globals::_stateMachine.getWindow());
        _scoreManager.render(*globals::_stateMachine.getWindow());

        if (_gameOver)
            {
                globals::_stateMachine.getWindow()->draw(_gameOverText);
            }
    }

void gameState::update(sf::Time deltaTime)
    {
        if (!_gameOver)
            {
                _home->update(deltaTime);
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
                        if (_scoreManager.getScore("leftGoal")->getScore() >= _maxScore && !_neverEnding)
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
                        if (_scoreManager.getScore("rightGoal")->getScore() >= _maxScore&& !_neverEnding)
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

        if ((_endGameCountdown.hasCountdownFinished() && _gameOver))
            {
                globals::_stateMachine.queueState(new menuState());
                globals::_stateMachine.popState();
            }
    }

void gameState::cleanup()
    {
        if (_home)
            {
                delete _home;
                _home = nullptr;
            }

        if (_away)
            {
                delete _away;
                _away = nullptr;
            }

        if (_ball)
            {
                delete _ball;
                _ball = nullptr;
            }

        _isInitialized = false;
    }

gameState::~gameState()
    {
        cleanup();
    }
