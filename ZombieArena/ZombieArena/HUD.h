#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class HUD
{
private:
    Sprite spriteGameOver;
    Sprite spriteAmmoIcon;

    Font font;

    Text pausedText;
    Text gameOverText;
    Text levelUpText;
    Text ammoText;
    Text scoreText;
    Text highScoreText;
    Text zombiesRemainingText;
    Text waveNumberText;

    RectangleShape healthBar;

    int bulletsInClip;
    int bulletsSpare;
    int score;
    int highScore;
    int wave;
    int numZombiesAlive;
public:
    HUD();

    void setBulletsInClip(int bulletsInClip);
    void setBulletsSpare(int bulletsSpare);
    void setScore(int score);
    void setHighScore(int highScore);
    void setWave(int wave);
    void setNumZombiesAlive(int numZombiesAlive);
    void resizeHealthBar(int playerHealth);

    void update();
    void draw(RenderWindow& window);
    void gameOver(RenderWindow& window);
    void gamePaused(RenderWindow& window);
    void gameLevelUp(RenderWindow& window);
};
