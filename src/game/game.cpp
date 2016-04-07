#include "game.hpp"
#include "globals.hpp"
#include <SFML/Graphics.hpp>

#include "../states/gameState.hpp"
#include "../states/menuState.hpp"

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

        globals::_textureManager.add("assets/textures/checkbox_check.png", "checkboxCheck");
        globals::_textureManager.add("assets/textures/checkbox_no_check.png", "checkboxNoCheck");

        globals::_fontManager.add("assets/font/Squares_Bold_Free.otf", "gameFont");
    }

void game::initializeControls()
    {
        globals::_keyboardManager.add(sf::Keyboard::Escape, [] () { globals::_stateMachine.popState(); }, true, PAUSE_MENU_STATE);
    }

void game::initialize()
    {
        initializeWindow();
        initializeTextures();
        initializeSounds();
        initializeControls();

        globals::_stateMachine.setWindow(app);
    }

void game::cleanup()
    {
        delete app;
        app = nullptr;

        if (globals::_stateMachine.getAllStates()->empty())
            {
                for (auto &state : *globals::_stateMachine.getAllStates())
                    {
                        globals::_stateMachine.popState();
                    }
            }
    }

void game::start()
    {
        initialize();

        globals::_stateMachine.queueState(new gameState(0, gameState::NEVER_ENDING_E_V_E));
        globals::_stateMachine.queueState(new menuState());

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
                                globals::_stateMachine.tick(deltaTime);
                            }
                        accumulator -= updateTime;
                    }

                globals::_stateMachine.render();
            }

        cleanup();
        globals::_stateMachine.cleanup();
    }

game::~game()
    {
        cleanup();
        globals::_stateMachine.cleanup();
    }
