// menuState.hpp
// the menu for the game. Opens on game start, and menu opened
#pragma once

#include "../UI/clickableButton.hpp"
#include "../UI/radioButton.hpp"
#include "state.hpp"

class menuState : public state
    {
        private:
            clickableButton _start;
            clickableButton _quit;

        public:
            menuState(sf::RenderWindow &app);

            void render(sf::RenderWindow &app);
            void update(sf::Time deltaTime);

            void initialize();

            void cleanup();
            ~menuState();
    };