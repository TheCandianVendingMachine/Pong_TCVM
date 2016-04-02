// scoreManager.hpp
// Manages all scores in the game
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <unordered_map>
#include <string>

#include "score.hpp"

class scoreManager
    {
        private:
            std::unordered_map<std::string, score> _scores;

        public:
            void addNewScore(const std::string &name, sf::Vector2f pos);
            void incrementScore(const std::string &name);

            score* getScore(const std::string &name);

            void render(sf::RenderWindow &app);
    };