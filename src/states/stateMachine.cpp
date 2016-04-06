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
                    }
            }

        _popState = false;
    }

stateMachine::stateMachine(sf::RenderWindow *window)
    {
        _popState = false;
        _closeWindow = false;
        _window = window;
    }

void stateMachine::queueState(state *newState)
    {
        _queuedState.push(newState);
    }

void stateMachine::pushState(state *newState)
    {
        _currentStates.push_back(newState);
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

void stateMachine::tick(sf::Time deltaTime)
    {
        // check if someone wants to close the window
        // do this at the start of the loop so it doesnt happen inbetween rendering and updating    
        if (_closeWindow)
            {
                _window->close();
            }

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
        
        handleInput();
        update(deltaTime);
    }

void stateMachine::handleInput()
    {
        sf::Event event;
        while (_window->pollEvent(event))
            {
                globals::_keyboardManager.handleInput(event, _currentStates.back()->getState());

                switch (event.type)
                    {
                        case sf::Event::Closed:
                            _window->close();
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

void stateMachine::render()
    {
        _window->clear(sf::Color::Black);
        if (!_currentStates.empty())
            {
                for (int i = (_currentStates.size() - 1); i >= 0; i--)
                    {
                        // render the state and check if they want to render overtop
                        // if they dont want to render overtop, break out of the loop
                        // if so, continue down the stack
                        
                        if (!_currentStates[i]->renderOvertop())
                            {
                                _currentStates[i]->render();
                                break;
                            }
                        else
                            {
                                // if the state wants to be rendered overtop the current state
                                // check if there is any state underneath
                                if (i >= 1)
                                    {
                                        // if so, render that state
                                        _currentStates[i - 1]->render();
                                        // and increment the count down so the state underneath doesnt render over the current state
                                        _currentStates[i--]->render();
                                    }
                                else// otherwise render like normal
                                    {
                                        _currentStates[i]->render();
                                    }
                            }
                    }
            }
        _window->display();
    }

void stateMachine::closeWindow()
    {
        _closeWindow = true;
    }

sf::RenderWindow *stateMachine::getWindow() const
    {
        return _window;
    }

void stateMachine::setWindow(sf::RenderWindow *window)
    {
        _window = window;
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
