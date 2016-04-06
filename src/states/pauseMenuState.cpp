#include "pauseMenuState.hpp"
#include "gameSetupState.hpp"

#include "../game/globals.hpp"

pauseMenuState::pauseMenuState()
    {
        _state = PAUSE_MENU_STATE;
        _renderOvertop = true;
        _updateUnderneath = false;

        _continue.setString("Continue");
        _continue.setColour(sf::Color::Red);
        _continue.setWindow(*globals::_stateMachine.getWindow());
        _continue.setPosition(_start.getPosition() - sf::Vector2f(0, (_continue.getBounds().height / 2) + 60.f));
        _continue.setFunction([] () { globals::_stateMachine.popState(); });

        _start.setFunction([] () 
            {
                globals::_stateMachine.popState();
                globals::_stateMachine.queueState(new gameSetupState);
            });

        _buttons.push_back(&_continue);
    }
