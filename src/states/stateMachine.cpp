#include "stateMachine.hpp"
#include "state.hpp"
#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

void stateMachine::addToQueue(state *newState)
    {
        _currentStates.push_back(newState);
    }

void stateMachine::popOffQueue()
    {
        if (_currentStates.size() > 0)
            {
                _currentStates.pop_front();
            }
    }

state *stateMachine::getCurrentState() const
    {
        if (_currentStates.size() > 0)
            {
                return _currentStates.front();
            }

        return nullptr;
    }

void stateMachine::update(sf::Time deltaTime)
    {
        if (_currentStates.size() > 0)
            {
                _currentStates.front()->update(deltaTime);
            }
    }

void stateMachine::render(sf::RenderWindow &app)
    {
        app.clear(sf::Color::Black);
        if (_currentStates.size() > 0)
            {
                _currentStates.front()->render(app);
            }
        app.display();
    }
