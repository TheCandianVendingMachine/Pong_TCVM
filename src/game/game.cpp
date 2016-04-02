#include "game.hpp"
#include "globals.hpp"
#include <SFML/Graphics.hpp>

#include "../states/gameState.hpp"

void game::handleInput(sf::RenderWindow &app)
    {
        sf::Event event;
        while (app.pollEvent(event))
            {
                switch (event.type)
                    {
                        case sf::Event::Closed:
                            app.close();
                            break;
                        case sf::Event::KeyPressed:
                            globals::_inputManager.handleInput(event.key.code);
                            break;
                        default:
                            break;
                    }
            }
    }

void game::initializeResources()
    {
        globals::_textureManager.add("assets/textures/paddle.png", "paddleTexture");
        globals::_textureManager.add("assets/textures/ball.png", "ballTexture");

        globals::_fontManager.add("assets/font/Squares_Bold_Free.otf", "gameFont");
    }

void game::start()
    {
        initializeResources();

        sf::RenderWindow app(sf::VideoMode(1200, 700), "Pong", sf::Style::Close);
        app.setFramerateLimit(60.0f);

        _stateMachine.addToQueue(new gameState(app.getSize()));

        sf::Clock deltaClock; 
        deltaClock.restart();

        float updateTime = 1.f / 60.f;

        sf::Time currentTime = deltaClock.getElapsedTime();
        float accumulator = 0.0f;

        while (app.isOpen())
            {
                sf::Time newTime = deltaClock.getElapsedTime();
                sf::Time deltaTime = newTime - currentTime;
                currentTime = newTime;

                accumulator += deltaTime.asSeconds();

                while (accumulator >= updateTime)
                    {
                        handleInput(app);
                        _stateMachine.update(deltaTime);
                        accumulator -= updateTime;
                    }

                _stateMachine.render(app);
            }
    }