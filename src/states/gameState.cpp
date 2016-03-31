#include "gameState.hpp"

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
    }

void gameState::render(sf::RenderWindow &app)
    {
        _player->draw(app);
        _opponent->draw(app);
        _ball->draw(app);
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
                _ball->initialize(sf::Vector2u(_goalRight.x, _goalRight.y));
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
