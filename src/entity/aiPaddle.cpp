#include "aiPaddle.hpp"

aiPaddle::aiPaddle(float maxHeight, float minHeight, sf::Vector2f startPos) : paddle(maxHeight, minHeight, startPos)
    {}

void aiPaddle::updateBallPos(sf::Vector2f ballPos, sf::Vector2f ballImpulse, sf::Time deltaTime)
    {
        sf::Vector2f newBallPos = ballPos + ((ballImpulse * 20.2f) * deltaTime.asSeconds());

        if ((newBallPos.y < _minHeight || newBallPos.y > _maxHeight) &&
            // if the paddle position minus the ball position is less than zero, it means its on the left side of the screen
            // make sure the ball wont go past the paddle to give a more "real" feel to the AI
            ((_sprite.getPosition().x - newBallPos.x < 0) ? newBallPos.x > _sprite.getPosition().x : newBallPos.x < _sprite.getPosition().x))
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
    }
