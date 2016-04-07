// menuState.hpp
// the menu for the game. Opens on game start, and menu opened
#pragma once

#include <vector>

#include "../UI/button.hpp"
#include "../UI/clickableButton.hpp"
#include "state.hpp"

class menuState : public state
    {
        protected:
            clickableButton _start;
            clickableButton _quit;

            std::vector<button*> _buttons;

        public:
            menuState();

            void render();
            void update(sf::Time deltaTime);

            virtual void initialize();

            virtual void cleanup();
            virtual ~menuState();
    };