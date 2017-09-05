#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Zombie
{
private:
    // Specify movement speed for each type
    const float BLOATER_SPEED = 40;
    const float CHASER_SPEED = 80;
    const float CRAWLER_SPEED = 20;

    // And the same for a health
    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;

    // Make each zombie vary its speed slightly
    const int MAX_VARRIANCE = 30;
    const int OFFSET = 101 - MAX_VARRIANCE;

    Vector2f m_Position;
    Sprite m_Sprite;

    float m_Speed;
    float m_Health;
    bool m_Alive;
public:
    Zombie();

    // Handling a bullet hit by the player
    bool hit();

    // Check whether the zombie is alive
    bool isAlive();

    // Spawn a new zombie on the level
    void spawn(float startX, float startY, int type, int seed);

    // Return a rectangle that is the position in the world
    FloatRect getPosition();

    // Get a copy of the sprite to draw
    Sprite getSprite();

    // Update the zombie each frame
    void update(float elapsedTime, Vector2f playerLocation);
};
