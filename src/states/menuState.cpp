#include "menuState.hpp"
#include "../game/globals.hpp"
#include "gameSetupState.hpp"

menuState::menuState()
    {
        _renderOvertop = true;
        _updateUnderneath = true;
        _isInitialized = false;
        _state = MENU_STATE;

        auto app = globals::_stateMachine.getWindow();

        _start.setString("Start Game");
        _start.setColour(sf::Color::Red);
        _start.setWindow(*app);
        _start.setPosition(sf::Vector2f((app->getSize().x / 2) - (_start.getText()->getLocalBounds().width / 2),
                          (app->getSize().y / 2) - (_start.getText()->getLocalBounds().height / 2) - 30));
        _start.setFunction([] () 
            {
                globals::_stateMachine.popState();
                globals::_stateMachine.queueState(new gameSetupState);
            });

        _quit.setString("Quit Game");
        _quit.setColour(sf::Color::Red);
        _quit.setWindow(*app);
        _quit.setPosition(sf::Vector2f((app->getSize().x / 2) - (_quit.getText()->getLocalBounds().width / 2),
                          (app->getSize().y / 2) - (_quit.getText()->getLocalBounds().height / 2) + 30));
        _quit.setFunction([&app] () 
            {
                globals::_stateMachine.closeWindow();
            });
    }

void menuState::render()
    {
        _start.render(*globals::_stateMachine.getWindow());
        _quit.render(*globals::_stateMachine.getWindow());
    }

void menuState::update(sf::Time deltaTime)
    {
        _start.update();
        _quit.update();
    }

void menuState::initialize()
    {
        _isInitialized = true;
    }

void menuState::cleanup()
    {
        _isInitialized = false;
    }

menuState::~menuState()
    {
    
    }
