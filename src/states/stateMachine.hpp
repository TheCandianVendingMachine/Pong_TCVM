// stateMachine.hpp
// handles all states in the game. Can push new states to the queue and pop them off as needed
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <deque>

class state;

class stateMachine
    {
        private:
            std::deque<state*> _currentStates;

        public:
            void addToQueue(state *newState);
            void popOffQueue();

            state* getCurrentState() const;

            // update the current state
            void update(sf::Time deltaTime);
            // render the current state
            void render(sf::RenderWindow &app);
    };