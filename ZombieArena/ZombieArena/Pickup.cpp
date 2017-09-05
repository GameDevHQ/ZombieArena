#include "stdafx.h"
#include "Pickup.h"
#include "TextureManager.h"


Pickup::Pickup(int type)
{
    m_Type = type;

    // Health pack
    if (type == 1)
    {
        m_Sprite = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/health_pickup.png"));
        m_Value = HEALTH_START_VALUE;
    }
    // Ammo pack
    else
    {
        m_Sprite = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/ammo_pickup.png"));
        m_Value = AMMO_START_VALUE;
    }

    m_Sprite.setOrigin(25, 25);
    m_SecondsToLive = static_cast<float>(START_SECONDS_TO_LIVE);
    m_SecondsToWait = static_cast<float>(START_WAIT_TIME);
}


void Pickup::setArena(IntRect arena)
{
    m_Arena.left = arena.left + 50;
    m_Arena.width = arena.width - 50;
    m_Arena.top = arena.top + 50;
    m_Arena.height = arena.height - 50;

    spawn();
}


void Pickup::spawn()
{
    // Spawn at a random location
    srand(static_cast<int>(time(NULL) / m_Type));
    float x = static_cast<float>(rand() % m_Arena.width);

    srand(static_cast<int>(time(NULL) * m_Type));
    float y = static_cast<float>(rand() % m_Arena.height);

    m_Spawned = true;
    m_SecondsSinceSpawn = 0;
    m_Sprite.setPosition(x, y);
}


FloatRect Pickup::getPosition()
{
    return m_Sprite.getGlobalBounds();
}


Sprite Pickup::getSprite()
{
    return m_Sprite;
}


void Pickup::update(float elapsedTime)
{
    if (m_Spawned)
    {
        m_SecondsSinceSpawn += elapsedTime;
    }
    else
    {
        m_SecondsSinceDeSpawn += elapsedTime;
    }

    // Do we need to hide a pickup?
    if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
    {
        m_Spawned = false;
        m_SecondsSinceDeSpawn = 0;
    }

    // Do we need to spawn a pickup once again?
    if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
    {
        spawn();
    }
}


bool Pickup::isSpawned()
{
    return m_Spawned;
}


int Pickup::gotIt()
{
    m_Spawned = false;
    m_SecondsSinceDeSpawn = 0;
    return m_Value;
}


void Pickup::upgrade()
{
    if (m_Type == 1)
    {
        m_Value += static_cast<int>(HEALTH_START_VALUE * .5);
    }
    else
    {
        m_Value += static_cast<int>(AMMO_START_VALUE * .5);
    }

    // Make them more frequent and last longer
    m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
    m_SecondsToWait -= (START_WAIT_TIME / 10);
}
