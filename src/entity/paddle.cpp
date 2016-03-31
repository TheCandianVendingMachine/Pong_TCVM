#include "paddle.hpp"
#include "../game/globals.hpp"
#include <SFML/Graphics.hpp>

paddle::paddle(float maxHeight, float minHeight, sf::Vector2f startPos) : _speed(200)
    {
        _minHeight = minHeight;
        _maxHeight = maxHeight;

        _sprite.setTexture(*globals::_textureManager.addTexture("assets/textures/paddle.png", "paddleTexture"));

        _sprite.setPosition(startPos);
        _impulse = sf::Vector2f(0, 0);
    }

void paddle::update(sf::Time deltaTime)
    {
        if (_sprite.getPosition().y + _sprite.getLocalBounds().height > _maxHeight)
            {
                _sprite.setPosition(_sprite.getPosition().x, _maxHeight - _sprite.getLocalBounds().height);
            }
        else if (_sprite.getPosition().y < _minHeight)
            {
                _sprite.setPosition(_sprite.getPosition().x, _minHeight);
            }

        _sprite.move(_impulse * deltaTime.asSeconds());
    }
