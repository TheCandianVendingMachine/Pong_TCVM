// aiPaddle.hpp
// the other paddle in pong
#pragma once

#include "paddle.hpp"

class ball;

class aiPaddle : public paddle
    {
        public:
            enum difficulty
                {
                    EASY,
                    MEDIUM,
                    HARD,
                };

        private:
            ball *_ball;

            float _accuracy;

            difficulty _difficulty;

        public:
            aiPaddle(float maxHeight, float minHeight, sf::Vector2f startPos, ball* currentBall, difficulty hardness);
            void update(sf::Time deltaTime);

    };