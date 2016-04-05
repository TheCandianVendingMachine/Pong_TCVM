#include "stateMachine.hpp"
#include "state.hpp"
#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

void stateMachine::popStateFromStack()
    {
        if (!_currentStates.empty())
            {
                // if the state isnt nullptr
                if (_currentStates.back())
                    {
                        _currentStates.back()->cleanup();
                        _currentStates.pop_back();
                        _popState = false;
                    }
            }
    }

stateMachine::stateMachine()
    {
        _popState = false;
    }

void stateMachine::queueState(state *newState)
    {
        _queuedState.push(newState);
    }

void stateMachine::pushState(state *newState)
    {
        _currentStates.push_back(newState);
        _currentStates.back()->initialize();
    }

void stateMachine::popState()
    {
        _popState = true;
    }

void stateMachine::reinitState()
    {
        _currentStates.back()->initialize();
    }

state *stateMachine::getCurrentState() const
    {
        if (!_currentStates.empty())
            {
                return _currentStates.back();
            }

        return nullptr;
    }

std::vector<state*> *stateMachine::getAllStates()
    {
        return &_currentStates;
    }

state *stateMachine::getStateUnderneath()
    {
        if (!_currentStates.empty() && _currentStates.size() > 1)
            {
                return _currentStates[_currentStates.size() - 2];
            }

        return nullptr;
    }

void stateMachine::tick(sf::RenderWindow &app, sf::Time deltaTime)
    {
        // check if a state is popped
        // We need this flag so a state isnt popped/cleaned up mid render/update. If it does happen, program crashes
        if (_popState)
            {
                // if so, pop it off the stack
                popStateFromStack();
            }

        // this makes sure that a state isnt changed mid render / update
        if (!_queuedState.empty())
            {
                for (int i = (_queuedState.size() - 1); i >= 0; i--)
                    {
                        pushState(_queuedState.front());
                        _queuedState.pop();
                    }
            }
        
        handleInput(app);
        update(deltaTime);
    }

void stateMachine::handleInput(sf::RenderWindow &app)
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
                            break;
                        default:
                            break;
                    }
            }
    }

void stateMachine::update(sf::Time deltaTime)
    {
        if (!_currentStates.empty())
            {
                for (int i = (_currentStates.size() - 1); i >= 0; i--)
                    {
                        // update the state and check if they want to have underneath states update
                        // if they dont want to update overtop, break out of the loop
                        // if so, continue down the stack
                        _currentStates[i]->update(deltaTime);
                        if (!_currentStates[i]->updateUnderneath())
                            {
                                break;
                            }
                    }
            }
    }

void stateMachine::render(sf::RenderWindow &app)
    {
        app.clear(sf::Color::Black);
        if (!_currentStates.empty())
            {
                for (int i = (_currentStates.size() - 1); i >= 0; i--)
                    {
                        // render the state and check if they want to render overtop
                        // if they dont want to render overtop, break out of the loop
                        // if so, continue down the stack
                        
                        if (!_currentStates[i]->renderOvertop())
                            {
                                _currentStates[i]->render(app);
                                break;
                            }
                        else
                            {
                                // if the state wants to be rendered overtop the current state
                                // check if there is any state underneath
                                if (i >= 1)
                                    {
                                        // if so, render that state
                                        _currentStates[i - 1]->render(app);
                                        // and increment the count down so the state underneath doesnt render over the current state
                                        _currentStates[i--]->render(app);
                                    }
                                else// otherwise render like normal
                                    {
                                        _currentStates[i]->render(app);
                                    }
                            }
                    }
            }
        app.display();
    }

void stateMachine::cleanup()
    {
        for (auto &topState : _currentStates)
            {
                if (topState)
                    {
                        topState->cleanup();
                        delete topState;
                        topState = nullptr;
                    }
            }
    }

stateMachine::~stateMachine()
    {
        cleanup();
    }
