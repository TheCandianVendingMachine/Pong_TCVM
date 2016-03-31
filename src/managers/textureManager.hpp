// textureManager.hpp
// manages all textures and makes sure there is only ever 1 pointer to them at a time
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class textureManager
    {
        private:
            std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
            
        public:
            /* get a texture in the texture map. Returns a pointer to it if it exists, otherwise a nulptr will be returned */
            sf::Texture *getTexture(const std::string &textureName);
            /* add a new texture to the map. If one exists or it succesfully adds it, it will return a pointer to the texture. Otherwise a nulptr is returned */
            sf::Texture *addTexture(const std::string &filepath, const std::string& textureName);
    };
