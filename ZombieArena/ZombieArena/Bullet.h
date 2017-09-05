#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Bullet
{
private:
    Vector2f m_Position;
    RectangleShape m_BulletShape;
    bool m_InFlight;
    float m_BulletSpeed;

    // What fraction of 1 pixel does the bullet travel, horizontally and vertically each frame? 
    float m_BulletDistanceX;
    float m_BulletDistanceY;

    // Boundaries of the bullet
    float m_MaxX;
    float m_MinX;
    float m_MaxY;
    float m_MinY;
public:
    Bullet();

    void stop();
    bool isInFlight();
    void shoot(float startX, float startY, float targetX, float targetY);
    FloatRect getPosition();
    RectangleShape getShape();
    void update(float elapsedTime);
};
