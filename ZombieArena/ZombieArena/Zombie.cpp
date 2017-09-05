#include "stdafx.h"
#include "Zombie.h"
#include "TextureManager.h"


Zombie::Zombie() :
m_Alive(true),
m_Speed(0),
m_Health(0)
{
}


bool Zombie::hit()
{
    m_Health--;

    if (m_Health < 0)
    {
        m_Alive = false;
        m_Sprite.setTexture(TextureManager::getInstance().getTexture("Resources/Graphics/blood.png"));
        return true;
    }
    return false;
}


bool Zombie::isAlive()
{
    return m_Alive;
}


void Zombie::spawn(float startX, float startY, int type, int seed)
{
    switch (type)
    {
        // Bloater
        case 0:
            m_Sprite = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/bloater.png"));
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            break;
        // Chaser
        case 1:
            m_Sprite = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/chaser.png"));
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            break;
        // Crawler
        case 2:
            m_Sprite = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/crawler.png"));
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            break;
    }

    // To make each zombie a unique lets modify their movement speed
    srand((int)time(0) * seed);
    float modifier = static_cast<float>((rand() % MAX_VARRIANCE) + OFFSET);

    modifier /= 100;
    m_Speed *= modifier;

    // Initialize the location of the zombie
    m_Position.x = startX;
    m_Position.y = startY;

    // Set its origin to the center
    m_Sprite.setOrigin(25, 25);

    // And update a current position
    m_Sprite.setPosition(m_Position);
}


FloatRect Zombie::getPosition()
{
    return m_Sprite.getGlobalBounds();
}


Sprite Zombie::getSprite()
{
    return m_Sprite;
}


void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    // Update the current position
    if (playerX > m_Position.x)
    {
        m_Position.x = m_Position.x + m_Speed * elapsedTime;
    }

    if (playerX < m_Position.x)
    {
        m_Position.x = m_Position.x - m_Speed * elapsedTime;
    }

    if (playerY > m_Position.y)
    {
        m_Position.y = m_Position.y + m_Speed * elapsedTime;
    }

    if (playerY < m_Position.y)
    {
        m_Position.y = m_Position.y - m_Speed * elapsedTime;
    }

    // Move the sprite
    m_Sprite.setPosition(m_Position);

    // Face the sprite in the correct direction
    float angle = static_cast<float>((atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141);
    m_Sprite.setRotation(angle);
}


