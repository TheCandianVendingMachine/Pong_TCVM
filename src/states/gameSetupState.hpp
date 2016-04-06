// gameSetupState.hpp
// The game setup. Allows users to customize game before actual play
#pragma once

#include "state.hpp"

#include "../UI/clickableButton.hpp"
#include "../UI/checkBox.hpp"
#include "../UI/radioButton.hpp"

#include <vector>

class gameSetupState : public state
    {
        private:
            clickableButton _confirm;
            clickableButton _back;

            // what game mode it will be. Versus AI, versus Player
            radioButton _gameModePVE;
            radioButton _gameModePVP;

            // never ending mode, on or off
            checkBox _neverEnding;

            std::vector<button*> _allButtons;

        public:
            gameSetupState();

            void render();
            void update(sf::Time deltaTime);

            void initialize();

            void cleanup();

            ~gameSetupState();
    };