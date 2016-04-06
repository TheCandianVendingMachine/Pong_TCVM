#include "gameSetupState.hpp"
#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

#include "menuState.hpp"
#include "gameState.hpp"

gameSetupState::gameSetupState()
    {
        _renderOvertop = true;
        _updateUnderneath = true;
        _isInitialized = false;
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
        _isInitialized = true;

        auto app = globals::_stateMachine.getWindow();

        sf::Vector2f halfWindowSize(app->getSize().x / 2, app->getSize().y / 2);
        const float spacing = 60;

        _gameModePVE.addLinkedButton(&_gameModePVP);
        _gameModePVP.addLinkedButton(&_gameModePVE);

        _gameModePVE.setWindow(*app);
        _gameModePVE.setTextures(globals::_textureManager.get("checkboxCheck"), globals::_textureManager.get("checkboxNoCheck"));
        _gameModePVE.setPreButtonString("Play Against Computer ");
        _gameModePVE.setColour(sf::Color::Red);
        _gameModePVE.setPosition(sf::Vector2f(halfWindowSize.x - (_gameModePVE.getText()->getLocalBounds().width / 2),
                                halfWindowSize.y - spacing - (_gameModePVE.getText()->getLocalBounds().height / 2)));
        _gameModePVE.setToggled(true);

        _gameModePVP.setWindow(*app);
        _gameModePVP.setTextures(globals::_textureManager.get("checkboxCheck"), globals::_textureManager.get("checkboxNoCheck"));
        _gameModePVP.setPreButtonString("Play Against Player ");
        _gameModePVP.setColour(sf::Color::Red);
        _gameModePVP.setPosition(sf::Vector2f(halfWindowSize.x - (_gameModePVP.getText()->getLocalBounds().width / 2),
                                halfWindowSize.y - (_gameModePVP.getText()->getLocalBounds().height / 2)));

        
        _neverEnding.setWindow(*app);
        _neverEnding.setTextures(globals::_textureManager.get("checkboxCheck"), globals::_textureManager.get("checkboxNoCheck"));
        _neverEnding.setPreButtonString("Never Ending Mode ");
        _neverEnding.setColour(sf::Color::Red);
        _neverEnding.setPosition(sf::Vector2f(halfWindowSize.x - (_neverEnding.getText()->getLocalBounds().width / 2),
                                 halfWindowSize.y + (spacing * 1.5) - (_neverEnding.getText()->getLocalBounds().height / 2)));

        _confirm.setWindow(*app);
        _confirm.setString("Confirm and Play");
        _confirm.setColour(sf::Color::Red);
        _confirm.setPosition(sf::Vector2f(halfWindowSize.x - (_confirm.getText()->getLocalBounds().width / 2),
                             _neverEnding.getPosition().y + (spacing * 2.5)));
        _confirm.setFunction([this] () 
            {
                gameState::gameMode selectedMode;
                if (_gameModePVE.getToggled())
                    {
                        if (_neverEnding.getToggled())
                            {
                                selectedMode = gameState::NEVER_ENDING_P_V_E;
                            }
                        else
                            {
                                selectedMode = gameState::P_V_E;
                            }
                    }
                else if (_gameModePVP.getToggled())
                    {
                        if (_neverEnding.getToggled())
                            {
                                selectedMode = gameState::NEVER_ENDING_P_V_P;
                            }
                        else
                            {
                                selectedMode = gameState::P_V_P;
                            }
                    }

                globals::_stateMachine.popAllStates();
                globals::_stateMachine.queueState(new gameState(10, selectedMode));
            });

        _back.setWindow(*app);
        _back.setString("Back");
        _back.setColour(sf::Color::Red);
        _back.setPosition(sf::Vector2f(halfWindowSize.x - (_back.getText()->getLocalBounds().width / 2),
                          _confirm.getPosition().y + (spacing * 0.75)));
        _back.setFunction([] ()
            {
                globals::_stateMachine.popState();
                globals::_stateMachine.queueState(new menuState());
            });

        _allButtons.push_back(&_confirm);
        _allButtons.push_back(&_back);
        _allButtons.push_back(&_gameModePVE);
        _allButtons.push_back(&_gameModePVP);
        _allButtons.push_back(&_neverEnding);
    }

void gameSetupState::cleanup()
    {
    
    }

gameSetupState::~gameSetupState()
    {
    
    }
