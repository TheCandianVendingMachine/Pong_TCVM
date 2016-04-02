// paddle.hpp
// the paddle in the game
#pragma once

#include "entity.hpp"

class paddle : public entity
    {
        protected:
            sf::Vector2f _startPos;

            float _minHeight;
            float _maxHeight;

            const float _speed;

        public:
            paddle(float maxHeight, float minHeight, sf::Vector2f startPos);
            void initialize();

            void update(sf::Time deltaTime);

    };