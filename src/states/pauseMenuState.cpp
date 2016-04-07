#include "pauseMenuState.hpp"
#include "gameSetupState.hpp"

#include "../game/globals.hpp"

pauseMenuState::pauseMenuState()
    {
        _state = PAUSE_MENU_STATE;
        _renderOvertop = true;
        _updateUnderneath = false;
    }

void pauseMenuState::initialize()
    {
        _isInitialized = true;
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

        _continue.setString("Continue");
        _continue.setColour(sf::Color::Red);
        _continue.setWindow(*globals::_stateMachine.getWindow());
        _continue.setPosition(_start.getPosition() - sf::Vector2f(0, (_continue.getBounds().height / 2) + 60.f));
        _continue.setFunction([] () { globals::_stateMachine.popState(); });

        _quit.setString("Quit Game");
        _quit.setColour(sf::Color::Red);
        _quit.setWindow(*app);
        _quit.setPosition(sf::Vector2f((app->getSize().x / 2) - (_quit.getText()->getLocalBounds().width / 2),
                          (app->getSize().y / 2) - (_quit.getText()->getLocalBounds().height / 2) + 30));
        _quit.setFunction([&app] () 
            {
                globals::_stateMachine.closeWindow();
            });

        _buttons.push_back(&_start);
        _buttons.push_back(&_quit);
        _buttons.push_back(&_continue);
    }
