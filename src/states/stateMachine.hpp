// stateMachine.hpp
// handles all states in the game. Can push new states to the queue and pop them off as needed
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <stack>

class state;

class stateMachine
    {
        private:
            std::stack<state*> _currentStates;
            state* _queuedState;

            // handles input for the current tick
            void handleInput(sf::RenderWindow &app);
            // update the current state
            void update(sf::Time deltaTime);

        public:
            stateMachine();

            void queueState(state *newState);
            void pushState(state *newState);
            void popState();

            state* getCurrentState() const;

            // handles current tick
            void tick(sf::RenderWindow &app, sf::Time deltaTime);
            // render the current state
            void render(sf::RenderWindow &app);
    };