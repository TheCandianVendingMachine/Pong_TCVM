// globals.hpp
// all global variables needed
#pragma once

#include "../states/stateMachine.hpp"

#include "../managers/resourceManager.hpp"
#include "../states/states.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class globals
    {
        public:
            static stateMachine _stateMachine;

            static resourceManager<sf::Texture> _textureManager;
            static resourceManager<sf::Font> _fontManager;

            static states _gameStates;
    };