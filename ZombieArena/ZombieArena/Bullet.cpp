#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet():
m_InFlight(false),
m_BulletSpeed(1000)
{
    m_BulletShape.setSize(Vector2f(2.f, 2.f));
}


void Bullet::stop()
{
    m_InFlight = false;
}


bool Bullet::isInFlight()
{
    return m_InFlight;
}


void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
    // Keep track the bullet
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    float gradient = (startX - targetX) / (startY - targetY);
    if (gradient < 0)
    {
        gradient *= -1;
    }

    // Set the "speed" horizontally and vertically
    float ratioXY = m_BulletSpeed / (1 + gradient);
    m_BulletDistanceY = ratioXY;
    m_BulletDistanceX = ratioXY * gradient;

    // Point the bullet in the right direction
    if (targetX < startX)
    {
        m_BulletDistanceX *= -1;
    }
    if (targetY < startY)
    {
        m_BulletDistanceY *= -1;
    }

    // Set a max range of 1000 pixels
    float range = 1000;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;

    // Position the bullet ready to be drawn
    m_BulletShape.setPosition(m_Position);
}


FloatRect Bullet::getPosition()
{
    return m_BulletShape.getGlobalBounds();
}


RectangleShape Bullet::getShape()
{
    return m_BulletShape;
}


void Bullet::update(float elapsedTime)
{
    // Calculate the new position of the bullet
    m_Position.x += m_BulletDistanceX * elapsedTime;
    m_Position.y += m_BulletDistanceY * elapsedTime;
    
    // And update the current position...
    m_BulletShape.setPosition(m_Position);

    // Does the bullet reach the boundaries?
    if (m_Position.x < m_MinX || m_Position.x > m_MaxX || m_Position.y < m_MinY || m_Position.y > m_MaxY)
    {
        m_InFlight = false;
    }
}
