#include "radioButton.hpp"

void radioButton::setButtonTexture()
    {
        if (_toggle)
            {
                _button.setTexture(*_toggledTexture);
            }
        else
            {
                _button.setTexture(*_nonToggledTexture);
            }
    }

radioButton::radioButton()
    {
        _toggle = false;

        _nonToggledTexture = nullptr;
        _toggledTexture = nullptr;
    }

void radioButton::setTextures(sf::Texture *toggled, sf::Texture *nonToggled)
    {
        _toggledTexture = toggled;
        _nonToggledTexture = nonToggled;

        setButtonTexture();
    }

void radioButton::setPosition(sf::Vector2f pos)
    {
        _button.setPosition(pos);
        _bounds = _button.getGlobalBounds();
    }

void radioButton::setScale(float amount)
    {
        _button.scale(amount, amount);
        _bounds = _button.getGlobalBounds();
    }

void radioButton::setSize(float X, float Y)
    {
        _button.scale(X / _button.getGlobalBounds().width, Y / _button.getGlobalBounds().height);
        _bounds = _button.getGlobalBounds();
    }

void radioButton::setSize(sf::Vector2f size)
    {
        setSize(size.x, size.y);
    }

const bool radioButton::getToggled() const
    {
        return _toggle;
    }

sf::Sprite *radioButton::getButton()
    {
        return &_button;
    }

void radioButton::render(sf::RenderWindow &app)
    {
        app.draw(_button);
    }

void radioButton::update()
    {
        _checkForMouse();
        if (_buttonClicked && !_clicked)
            {
                _toggle = !_toggle;
                _clicked = true;
                setButtonTexture();
            }
        else if (!_buttonClicked && _clicked)
            {
                _clicked = false;
            }

    }
