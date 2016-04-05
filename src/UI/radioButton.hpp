// radioButton.hpp
// a toggleable button. Very simple
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "button.hpp"

class radioButton : public button
    {
        private:
            sf::Sprite _button;

            sf::Texture *_toggledTexture;
            sf::Texture *_nonToggledTexture;
            
            bool _toggle;
            bool _clicked;

        private:
            void setButtonTexture();

        public:
            radioButton();

            void setTextures(sf::Texture *toggled, sf::Texture *nonToggled);
            void setPosition(sf::Vector2f pos);
            void setScale(float amount);
            
            void setSize(float X, float Y);
            void setSize(sf::Vector2f size);

            const bool getToggled() const;
            sf::Sprite *getButton();


            void render(sf::RenderWindow &app);
            void update();
    };