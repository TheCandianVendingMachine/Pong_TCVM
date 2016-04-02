// player.hpp
// the player
#pragma once

#include "paddle.hpp"
#include <SFML/Window/Keyboard.hpp>

class player : public paddle
    {
        public:
            player(float maxHeight, float minHeight, sf::Vector2f startPos);

    };