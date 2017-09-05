#include "stdafx.h"
#include "TextureManager.h"


TextureManager& TextureManager::getInstance()
{
    static TextureManager* instance = new TextureManager();
    return *instance;
}

Texture& TextureManager::getTexture(const std::string & filename)
{
    auto keyValuePair = m_Textures.find(filename);

    if (keyValuePair != m_Textures.end())
    {
        return keyValuePair->second;
    }
    else
    {
        Texture& texture = m_Textures[filename];

        // Load the texture from file in the usual way
        texture.loadFromFile(filename);
        return texture;
    }

}


