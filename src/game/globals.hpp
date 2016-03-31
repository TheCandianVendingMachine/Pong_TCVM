// globals.hpp
// all global variables needed
#pragma once

#include "../managers/textureManager.hpp"
#include "../managers/inputManager.hpp"
#include "../states/states.hpp"

class globals
    {
        public:
            static textureManager _textureManager;
            static inputManager _inputManager;

            static states _gameStates;
    };