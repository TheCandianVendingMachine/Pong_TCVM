#include "menuState.hpp"
#include "../game/globals.hpp"
#include "gameState.hpp"

menuState::menuState(sf::RenderWindow &app)
    {
        _renderOvertop = true;
        _updateUnderneath = true;
        _isInitialized = false;
        _state = MENU_STATE;

        _start.setString("Start Game");
        _start.setColour(sf::Color::Red);
        _start.setWindow(app);
        _start.setPosition(sf::Vector2f((app.getSize().x / 2) - (_start.getText()->getLocalBounds().width / 2),
                          (app.getSize().y / 2) - (_start.getText()->getLocalBounds().height / 2) - 30));
        _start.setFunction([&app] () 
            {
                globals::_stateMachine.queueState(new gameState(app.getSize(), 10, gameState::E_V_E));
                globals::_stateMachine.popState();
            });

        _quit.setString("Quit Game");
        _quit.setColour(sf::Color::Red);
        _quit.setWindow(app);
        _quit.setPosition(sf::Vector2f((app.getSize().x / 2) - (_quit.getText()->getLocalBounds().width / 2),
                          (app.getSize().y / 2) - (_quit.getText()->getLocalBounds().height / 2) + 30));

        _quit.setFunction([&app] () 
            {
                app.close();
            });
    }

void menuState::render(sf::RenderWindow &app)
    {
        _start.render(app);
        _quit.render(app);
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
