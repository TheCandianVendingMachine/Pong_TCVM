// aiPaddle.hpp
// the other paddle in pong
#pragma once

#include "paddle.hpp"

class aiPaddle : public paddle
    {
        public:
            aiPaddle(float maxHeight, float minHeight, sf::Vector2f startPos);

            void updateBallPos(sf::Vector2f ballPos, sf::Vector2f ballImpulse, sf::Time deltaTime);

    };