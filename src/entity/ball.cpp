#include "ball.hpp"
#include "../game/globals.hpp"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

ball::ball(sf::Vector2u windowSize)
    : _speed(400.f),
    _minSpeed(300.f),
    _maxBounceAngle(75.0f)
    {
        _sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
        _startPos = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
        initialize();

        _windowSize = windowSize;

        _sprite.setTexture(*globals::_textureManager.get("ballTexture"));

        _gameStartDirectionModifier = -1;
    }

void ball::initialize()
    {
        _sprite.setPosition(_startPos);
        _impulse = sf::Vector2f(_speed * _gameStartDirectionModifier, 0);
    }

void ball::update(sf::Time deltaTime)
    {
        if (_sprite.getPosition().y - (_sprite.getLocalBounds().height / 2) < 0 ||
            _sprite.getPosition().y + (_sprite.getLocalBounds().height / 2) > _windowSize.y)
            {
                _impulse.y *= -1;

                if (_sprite.getPosition().y - (_sprite.getLocalBounds().height / 2) < 0)
                    {
                        _sprite.setPosition(_sprite.getPosition().x, 0 + (_sprite.getLocalBounds().height / 2));
                    }
                else
                    {
                        _sprite.setPosition(_sprite.getPosition().x, _windowSize.y - (_sprite.getLocalBounds().height / 2));
                    }
            }

        if (abs(_impulse.x) < _minSpeed)
            {
                _impulse.x > 0 ? _impulse.x = _minSpeed : _impulse.x = -_minSpeed;
            }

        _sprite.move(_impulse * deltaTime.asSeconds());
    }

void ball::setGameStartDirection(int direction)
    {
        _gameStartDirectionModifier = direction;
    }

/* use basic overlap check to check for collision */
void ball::collide(sf::Sprite &other)
    {
        sf::Vector2f centerFirst(_sprite.getPosition().x + (_sprite.getLocalBounds().width / 2),
                                 _sprite.getPosition().y + (_sprite.getLocalBounds().height / 2));

        sf::Vector2f centerSecond(other.getPosition().x + (other.getLocalBounds().width / 2),
                                  other.getPosition().y + (other.getLocalBounds().height / 2));


        sf::Vector2f distance(centerFirst - centerSecond);
        sf::Vector2f minDistance((_sprite.getLocalBounds().width / 2) + (other.getLocalBounds().width / 2),
                                 (_sprite.getLocalBounds().height / 2) + (other.getLocalBounds().height / 2));

        // if ball collides with a sprite, bounce off
        if (abs(distance.x) < minDistance.x && abs(distance.y) < minDistance.y)
            {
                sf::Vector2f overlap(distance.x > 0 ? minDistance.x - distance.x : -minDistance.x - distance.x,
                                     distance.y > 0 ? minDistance.y - distance.y : -minDistance.y - distance.y);


                // find the new angle of bounce using trig
                float angle = std::atan2(centerSecond.y - centerFirst.y, centerSecond.x - centerFirst.x);
                // and get new velocity
                _impulse = sf::Vector2f(std::cos(angle), std::sin(angle)) * -_speed;

                // move the ball out of the paddle to avoid the ball getting stuck in the paddle
                if (abs(overlap.x) > abs(overlap.y))
                    {
                        // Y is shallow axis
                        _sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + overlap.y);
                    }
                else
                    {
                        // X is shallow axis
                        _sprite.setPosition(_sprite.getPosition().x + overlap.x, _sprite.getPosition().y);
                    }
            }
    }
