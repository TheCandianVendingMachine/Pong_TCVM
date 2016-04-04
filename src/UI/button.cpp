#include "button.hpp"
#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

button::button()
    {
        _text.setFont(*globals::_fontManager.get("gameFont"));
        _text.setString("");
        _textColour = _text.getColor();

        _onButtonPress = [] () {};
    }

void button::setWindow(sf::RenderWindow &app)
    {
        _app = &app;
    }

void button::setString(const std::string &buttonText)
    {
        _text.setString(buttonText);
    }

void button::setFunction(std::function<void()> onButtonPress)
    {
        _onButtonPress = onButtonPress;
    }

void button::setColour(sf::Color colour)
    {
        _text.setColor(colour);
        _textColour = colour;
    }

void button::setSize(unsigned int size)
    {
        _text.setCharacterSize(size);
    }

void button::setPosition(sf::Vector2f pos)
    {
        _text.setPosition(pos);
    }

sf::Vector2f button::getPosition()
    {
        return _text.getPosition();
    }

sf::Text *button::getText()
    {
        return &_text;
    }

void button::update()
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*_app);
        sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);

        if (_text.getGlobalBounds().contains(mousePosFloat))
            {
                _text.setColor(sf::Color::White);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        _onButtonPress();
                    }
            }
        else
            {
                _text.setColor(_textColour);
            }
    }

void button::render(sf::RenderWindow &app)
    {
        app.draw(_text);
    }

const std::string &button::getString()
    {
        return _text.getString();
    }
