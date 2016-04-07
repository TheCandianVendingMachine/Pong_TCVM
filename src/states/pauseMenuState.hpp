// pauseMenuState.hpp
// a pause menu for ingame. Same as the menuState, except is has a "continue" button 
#pragma once

#include "menuState.hpp"

class pauseMenuState : public menuState
    {
        private:
            clickableButton _continue;

        public:
            pauseMenuState();

            void initialize();

    };