#include "gameSetupState.hpp"
#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

#include "menuState.hpp"
#include "gameState.hpp"

gameSetupState::gameSetupState()
    {
        _renderOvertop = true;
        _updateUnderneath = true;
        _state = GAMEPLAY_OPTION_STATE;


        initialize();
    }

void gameSetupState::render()
    {
        for (auto &currentButton : _allButtons)
            {
                currentButton->render(*globals::_stateMachine.getWindow());
            }
    }

void gameSetupState::update(sf::Time deltaTime)
    {
        for (auto &currentButton : _allButtons)
            {
                currentButton->update();
            }
    }

void gameSetupState::initialize()
    {
        auto app = globals::_stateMachine.getWindow();

        sf::Vector2f halfWindowSize(app->getSize().x / 2, app->getSize().y / 2);
        const float spacing = 25;

        _gameMode.setWindow(*app);
        _gameMode.setTextures(globals::_textureManager.get("checkboxCheck"), globals::_textureManager.get("checkboxNoCheck"));
        _gameMode.setPreButtonString("Game Mode ");
        _gameMode.setColour(sf::Color::Red);
        _gameMode.setPosition(sf::Vector2f(halfWindowSize.x - (_gameMode.getText()->getLocalBounds().width / 2),
                              halfWindowSize.y - spacing - (_gameMode.getText()->getLocalBounds().height / 2)));

        
        _neverEnding.setWindow(*app);
        _neverEnding.setTextures(globals::_textureManager.get("checkboxCheck"), globals::_textureManager.get("checkboxNoCheck"));
        _neverEnding.setPreButtonString("Never Ending Mode ");
        _neverEnding.setColour(sf::Color::Red);
        _neverEnding.setPosition(sf::Vector2f(halfWindowSize.x - (_neverEnding.getText()->getLocalBounds().width / 2),
                                 halfWindowSize.y + spacing - (_neverEnding.getText()->getLocalBounds().height / 2)));


        _back.setWindow(*app);
        _back.setString("Back");
        _back.setColour(sf::Color::Red);
        _back.setFunction([] ()
            {
                globals::_stateMachine.queueState(new menuState());
                globals::_stateMachine.popState();
            });


        _confirm.setWindow(*app);
        _confirm.setString("Confirm and Play");
        _confirm.setColour(sf::Color::Red);
        _confirm.setPosition(sf::Vector2f(halfWindowSize.x - (_confirm.getText()->getLocalBounds().width / 2),
                             0));
        _confirm.setFunction([this] () 
            {
                gameState::gameMode selectedMode;
                if (_neverEnding.getToggled())
                    {
                        selectedMode = gameState::NEVER_ENDING_P_V_E;
                    }
                else
                    {
                        selectedMode = gameState::P_V_E;
                    }

                globals::_stateMachine.popState();
                globals::_stateMachine.queueState(new gameState(/*_maxScore.getValue()*/1, selectedMode));
            });


        _allButtons.push_back(&_confirm);
        _allButtons.push_back(&_back);
        _allButtons.push_back(&_gameMode);
        _allButtons.push_back(&_neverEnding);
    }

void gameSetupState::cleanup()
    {
    
    }

gameSetupState::~gameSetupState()
    {
    
    }
