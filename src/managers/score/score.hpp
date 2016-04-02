// score.hpp
// a way to simply add scores to an object. Manages the text so it can be rendered
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class score
    {
        private:
            sf::Text _text;
            int _score;

        public:
            score();

            void increment();

            int getScore() const;
            const std::string &getScoreAsString();

            sf::Text &getText();

            void render(sf::RenderWindow &app);
    };