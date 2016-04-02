// aiPaddle.hpp
// the other paddle in pong
#pragma once

#include "paddle.hpp"

class ball;

class aiPaddle : public paddle
    {
        private:
            ball *_ball;

        public:
            aiPaddle(float maxHeight, float minHeight, sf::Vector2f startPos, ball* currentBall);
            void update(sf::Time deltaTime);

    };