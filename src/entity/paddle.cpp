#include "paddle.hpp"
#include "../game/globals.hpp"
#include <SFML/Graphics.hpp>

paddle::paddle(float maxHeight, float minHeight, sf::Vector2f startPos) : _speed(200)
    {
        _minHeight = minHeight;
        _maxHeight = maxHeight;

        _sprite.setTexture(*globals::_textureManager.get("paddleTexture"));

        _startPos = startPos;

        initialize();
    }

void paddle::initialize()
    {
        _sprite.setPosition(_startPos - sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
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
