// button.hpp
// basic button class. Has a std::function that executes when button is pressed
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>

class button
    {
        private:
            sf::RenderWindow *_app;

            sf::Text _text;
            sf::Color _textColour;

            std::function<void()> _onButtonPress;

        public:
            button();
            
            void setWindow(sf::RenderWindow &app);

            void setString(const std::string &buttonText);
            void setFunction(std::function<void()> onButtonPress);
            
            void setColour(sf::Color colour);
            void setSize(unsigned int size);
            void setPosition(sf::Vector2f pos);

            sf::Vector2f getPosition();

            sf::Text *getText();

            void update();
            void render(sf::RenderWindow &app);

            const std::string &getString();
    };