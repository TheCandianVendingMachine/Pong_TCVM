#include "score.hpp"
#include "../../game/globals.hpp"

score::score()
    {
        _score = 0;

        _text.setFont(*globals::_fontManager.get("gameFont"));
        _text.setString(std::to_string(_score));
    }

void score::increment()
    {
        ++_score;
        _text.setString(std::to_string(_score));
    }

void score::setScore(int amount)
    {
        _score = amount;
    }

int score::getScore() const
    {
        return _score;
    }

const std::string & score::getScoreAsString()
    {
        return _text.getString();
    }

sf::Text &score::getText()
    {
        return _text;
    }

void score::render(sf::RenderWindow &app)
    {
        app.draw(_text);
    }
