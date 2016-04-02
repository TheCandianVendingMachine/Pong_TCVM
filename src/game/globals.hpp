// globals.hpp
// all global variables needed
#pragma once

#include "../managers/resourceManager.hpp"
#include "../managers/input/inputManager.hpp"
#include "../states/states.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class globals
    {
        public:
            static resourceManager<sf::Texture> _textureManager;
            static resourceManager<sf::Font> _fontManager;

            static inputManager _inputManager;

            static states _gameStates;
    };