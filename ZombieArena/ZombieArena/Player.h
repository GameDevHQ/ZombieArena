#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;


class Player
{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    
    // Players position
    Vector2f m_Position;

    // Rendered sprite
    Sprite m_Sprite;
    Texture m_Texture;

    // Current screen resolution
    Vector2f m_Resolution;

    // Size is the current arena
    IntRect m_Arena;

    // How big is each tile of the arena
    int m_TileSize;

    // Which directions is the player currently moving in
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;

    // How much health has the player got?
    int m_Health;

    // What is the maximum health the player can have
    int m_MaxHealth;

    // When was the player last hit
    Time m_LastHit;

    // Speed in pixels per second
    float m_Speed;
public:
    Player();

    void spawn(IntRect arena, Vector2f resolution, int tileSize);
    void resetPlayerStats();

    // Handle the player getting hit by a zombie
    bool hit(Time timeHit);

    // How long ago was the player last hit
    Time getLastHitTime();

    // Where is the player
    FloatRect getPosition();

    // Where is the center of the player
    Vector2f getCenter();

    // Which angle is the player facing
    float getRotation();

    // Send a copy of the sprite to main
    Sprite getSprite();

    // The next four functions move the player
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // Stop the player moving in a specific direction
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    // We will call this function once every frame
    void update(float elapsedTime, Vector2i mousePosition);

    // Give player a speed boost
    void upgradeSpeed();

    // Give the player some health
    void upgradeHealth();

    // Increase the maximum amount of health the player can have
    void increaseHealthLevel(int amount);

    // How much health has the player currently got?
    int getHealth();
};
