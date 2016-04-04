#include "aiPaddle.hpp"
#include "ball.hpp"

aiPaddle::aiPaddle(float maxHeight, float minHeight, sf::Vector2f startPos, ball* currentBall, difficulty hardness) : paddle(maxHeight, minHeight, startPos)
    {
        _ball = currentBall;
        _difficulty = hardness;

        switch (_difficulty)
            {
                case aiPaddle::EASY:
                    _accuracy = 10.00f;
                    break;
                case aiPaddle::MEDIUM:
                    _accuracy = 15.00;
                    break;
                case aiPaddle::HARD:
                    _accuracy = 25.00f;
                    break;
                default:
                    _accuracy = 20.00f;
                    break;
            }
    }

void aiPaddle::update(sf::Time deltaTime)
    {
        sf::Vector2f newBallPos = _ball->getPosition() + ((_ball->getImpulse() * _accuracy) * deltaTime.asSeconds());

        if ((newBallPos.y < _minHeight || newBallPos.y > _maxHeight) &&
            // if the paddle position minus the ball position is less than zero, it means its on the left side of the screen
            // make sure the ball wont go past the paddle to give a more "real" feel to the AI
            ((_sprite.getPosition().x - newBallPos.x < 0) ? newBallPos.x > (_sprite.getPosition().x + (_sprite.getLocalBounds().width / 2)) : 
            newBallPos.x < (_sprite.getPosition().x - (_sprite.getLocalBounds().width / 2))))
            {
                newBallPos.y = _sprite.getPosition().y + (_sprite.getLocalBounds().height / 2);
            }

        if ((_sprite.getPosition().y + (_sprite.getLocalBounds().height / 2)) + 10 > newBallPos.y)
            {
                _impulse.y = -_speed;
            }
        else if ((_sprite.getPosition().y + (_sprite.getLocalBounds().height / 2)) - 10 < newBallPos.y)
            {
                _impulse.y = _speed;
            }
        else
            {
                _impulse.y = 0.f;
            }

        if (_sprite.getPosition().y + _sprite.getLocalBounds().height > _maxHeight)
            {
                _sprite.setPosition(_sprite.getPosition().x, _maxHeight - _sprite.getLocalBounds().height);
            }
        else if (_sprite.getPosition().y < _minHeight)
            {
                _sprite.setPosition(_sprite.getPosition().x, _minHeight);
            }

        _sprite.move(_impulse * deltaTime.asSeconds());
    }