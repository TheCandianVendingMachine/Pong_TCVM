// ball.hpp
// the ball
#pragma once

#include "entity.hpp"

class ball : public entity
    {
            sf::Vector2u _windowSize;

            const float _speed;
            const float _minSpeed;
            const float _maxBounceAngle;

        public:
            ball(sf::Vector2u windowSize);
            void initialize(sf::Vector2u windowSize);

            void update(sf::Time deltaTime);

            void collide(sf::Sprite &other);

    };