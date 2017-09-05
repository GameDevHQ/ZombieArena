#pragma once
#include <map>
#include <SFML/Graphics.hpp>
using namespace sf;


class TextureManager
{
private:
    std::map<std::string, Texture> m_Textures;
public:
    static TextureManager& getInstance();
    Texture& getTexture(const std::string& filename);
private:
    TextureManager() = default;
    ~TextureManager() = default;
    TextureManager(const TextureManager&);                 
    TextureManager& operator=(const TextureManager&); 
};
