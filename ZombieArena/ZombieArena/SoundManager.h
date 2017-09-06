#pragma once
#include <map>
#include <SFML/Audio.hpp>
using namespace sf;


class SoundManager
{
private:
    std::map<std::string, SoundBuffer*> soundBuffers;
    std::map<std::string, Sound*> sounds;
public:
    static SoundManager& getInstance();
    void play(const std::string& filename);
private:
    SoundManager();
    ~SoundManager() = default;
    SoundManager(const SoundManager&);
    SoundManager& operator=(const SoundManager&);
};
