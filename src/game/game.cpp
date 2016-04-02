#include "game.hpp"
#include "globals.hpp"
#include <SFML/Graphics.hpp>

#include "../states/gameState.hpp"

void game::initializeWindow()
    {
        app = new sf::RenderWindow(sf::VideoMode(1200, 700), "Pong", sf::Style::Close);
        app->setFramerateLimit(60.0f);
    }

void game::initializeSounds()
    {}

void game::initializeTextures()
    {
        globals::_textureManager.add("assets/textures/paddle.png", "paddleTexture");
        globals::_textureManager.add("assets/textures/ball.png", "ballTexture");

        globals::_fontManager.add("assets/font/Squares_Bold_Free.otf", "gameFont");
    }

void game::initialize()
    {
        initializeWindow();
        initializeTextures();
        initializeSounds();

    }

void game::cleanup()
    {
        delete app;
        app = nullptr;
    }

void game::start()
    {
        initialize();

        globals::_stateMachine.queueState(new gameState(app->getSize(), 1000, gameState::E_V_E));

        sf::Clock deltaClock; 
        deltaClock.restart();

        float updateTime = 1.f / 60.f;

        sf::Time currentTime = deltaClock.getElapsedTime();
        float accumulator = 0.0f;

        while (app->isOpen())
            {
                sf::Time newTime = deltaClock.getElapsedTime();
                sf::Time deltaTime = newTime - currentTime;
                currentTime = newTime;

                accumulator += deltaTime.asSeconds();

                while (accumulator >= updateTime)
                    {
                        if (app->hasFocus())
                            {
                                globals::_stateMachine.tick(*app, deltaTime);
                            }
                        accumulator -= updateTime;
                    }

                globals::_stateMachine.render(*app);
            }

        cleanup();
    }