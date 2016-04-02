#include "stateMachine.hpp"
#include "state.hpp"
#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

stateMachine::stateMachine()
    {
        _queuedState = nullptr;
    }

void stateMachine::queueState(state *newState)
    {
        _queuedState = newState;
    }

void stateMachine::pushState(state *newState)
    {
        _currentStates.push(newState);
    }

void stateMachine::popState()
    {
        if (!_currentStates.empty())
            {
                _currentStates.pop();
            }
    }

state *stateMachine::getCurrentState() const
    {
        if (!_currentStates.empty())
            {
                return _currentStates.top();
            }

        return nullptr;
    }

void stateMachine::tick(sf::RenderWindow &app, sf::Time deltaTime)
    {
        // this makes sure that a state isnt changed mid render / update
        if (_queuedState)
            {
                pushState(_queuedState);
                _queuedState = nullptr;
            }
        
        handleInput(app);
        update(deltaTime);
    }

void stateMachine::handleInput(sf::RenderWindow & app)
    {
        sf::Event event;
        while (app.pollEvent(event))
            {
                switch (event.type)
                    {
                        case sf::Event::Closed:
                            app.close();
                            break;
                        case sf::Event::KeyPressed:
                            globals::_inputManager.handleInput(event.key.code);
                            break;
                        default:
                            break;
                    }
            }
    }

void stateMachine::update(sf::Time deltaTime)
    {
        if (_currentStates.size() > 0)
            {
                _currentStates.top()->update(deltaTime);
            }
    }

void stateMachine::render(sf::RenderWindow &app)
    {
        app.clear(sf::Color::Black);
        if (_currentStates.size() > 0)
            {
                _currentStates.top()->render(app);
            }
        app.display();
    }
