#include "textureManager.hpp"

sf::Texture *textureManager::getTexture(const std::string &textureName)
    {
        auto it = m_textures.find(textureName);
        if (it != m_textures.end())
            {
                return it->second.get();
            }

        return nullptr;
    }

sf::Texture *textureManager::addTexture(const std::string &filepath, const std::string &textureName)
    {
        sf::Texture *newTexture = getTexture(textureName);
        if (newTexture)
            {
                return newTexture;
            }

        newTexture = new sf::Texture;
        if (newTexture->loadFromFile(filepath))
            {
                m_textures[textureName] = std::make_shared<sf::Texture>(*newTexture);
                return m_textures[textureName].get();
            }

        return nullptr;
    }