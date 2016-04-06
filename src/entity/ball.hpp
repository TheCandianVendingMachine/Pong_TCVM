// ball.hpp
// the ball
#pragma once

#include "entity.hpp"

class ball : public entity
    {
        private:
            sf::Vector2u _windowSize;
            sf::Vector2f _startPos;

            int _gameStartDirectionModifier;

            const float _speed;
            const float _minSpeed;
            const float _maxBounceAngle;

        public:
            ball(sf::Vector2u windowSize);
            void initialize();

            void update(sf::Time deltaTime);

            void setGameStartDirection(int direction);

            void collide(sf::Sprite &other);

    };