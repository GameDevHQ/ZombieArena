#include "stdafx.h"
#include "SoundManager.h"
#include <sstream>


SoundManager::SoundManager()
{
    std::vector<std::string> soundNames = {
        "hit", "splat", "shoot", 
        "reload", "reload_failed", "powerup", 
        "pickup"
    };

    for (auto soundName : soundNames)
    {
        std::stringstream ss;
        ss << "Resources/Sound/" << soundName << ".wav";
        std::string filename = ss.str();

        SoundBuffer* soundBuffer = new SoundBuffer();
        soundBuffer->loadFromFile(filename);
        Sound* sound = new Sound();
        sound->setBuffer(*soundBuffer);

        soundBuffers[filename] = soundBuffer;
        sounds[filename] = sound;
    }
}


SoundManager& SoundManager::getInstance()
{
    static SoundManager* instance = new SoundManager();
    return *instance;
}


void SoundManager::play(const std::string& filename)
{
    std::map<std::string, Sound*>::iterator it = sounds.find(filename);
    if (it != sounds.end())
    {
        it->second->play();
    }
}
