// state.hpp
// base class for a basic game state
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include <string>

#include "states.hpp"

class state
    {
        protected:
            states _state;

        public:
            state() = default;

            virtual void render(sf::RenderWindow &app) = 0;
            virtual void update(sf::Time deltaTime) = 0;

            const states getState() const;

            virtual ~state();
    };