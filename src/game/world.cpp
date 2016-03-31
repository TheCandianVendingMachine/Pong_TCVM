#include "world.hpp"
#include <SFML/Graphics.hpp>

world::world()
    {
        _currentMode = NONE;

        _ball = nullptr;
        _player = nullptr;
        _aiLeft = nullptr;
        _aiRight = nullptr;
    }

world::world(sf::Vector2u windowSize)
    {
        _currentMode = NONE;
        _windowSize = windowSize;

        _ball = nullptr;
        _player = nullptr;
        _aiLeft = nullptr;
        _aiRight = nullptr;
    }

void world::setGameMode(gameMode mode)
    {}

void world::update(sf::Time deltaTime)
    {}

void world::draw(sf::RenderWindow &app)
    {
        _ball->draw(app);

        switch (_currentMode)
            {
                case world::AI_V_AI:
                    _aiRight->draw(app);
                    _aiLeft->draw(app);
                    break;
                case world::P_V_AI:
                    _aiRight->draw(app);
                    _player->draw(app);
                    break;
                case world::P_V_P:
                    _player->draw(app);
                    break;
                case world::NONE:
                    break;
                default:
                    break;
            }
    }

world::~world()
    {
        delete _ball;
        delete _player;
        delete _aiLeft;
        delete _aiRight;

        _ball = nullptr;
        _player = nullptr;
        _aiLeft = nullptr;
        _aiRight = nullptr;
    }
