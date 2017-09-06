#include "stdafx.h"
#include <sstream>
#include "HUD.h"
#include "TextureManager.h"



HUD::HUD():
bulletsInClip(0),
score(0),
highScore(0),
wave(0),
numZombiesAlive(0)
{
    // Game over screen
    spriteGameOver = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/background.png"));
    spriteGameOver.setPosition(0, 0);

    // Ammo icon for the HUD
    spriteAmmoIcon = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/ammo_icon.png"));
    spriteAmmoIcon.setPosition(20, 980);

    // Font for HUD
    font.loadFromFile("Resources/Fonts/Kust.ttf");

    // Paused text for HUD
    pausedText.setFont(font);
    pausedText.setCharacterSize(155);
    pausedText.setFillColor(Color::White);
    pausedText.setPosition(400, 400);
    pausedText.setString("Press Enter \n to continue");

    // Game Over text for HUD
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(125);
    gameOverText.setFillColor(Color::White);
    gameOverText.setPosition(250, 850);
    gameOverText.setString("Press Enter to play");

    // Level-up for the player
    levelUpText.setFont(font);
    levelUpText.setCharacterSize(80);
    levelUpText.setFillColor(Color::White);
    levelUpText.setPosition(150, 250);
    std::stringstream levelUpStream;
    levelUpStream <<
        "Num1 - Increased rate of fire" << std::endl <<
        "Num2 - Increased clip size(next reload)" << std::endl <<
        "Num3 - Increased max health" << std::endl <<
        "Num4 - Increased run speed" << std::endl <<
        "Num5 - More and better health pickups" << std::endl <<
        "Num6 - More and better ammo pickups";
    levelUpText.setString(levelUpStream.str());

    // Ammo
    ammoText.setFont(font);
    ammoText.setCharacterSize(55);
    ammoText.setFillColor(Color::White);
    ammoText.setPosition(200, 980);

    // Score
    scoreText.setFont(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 0);

    // High Score
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(55);
    highScoreText.setFillColor(Color::White);
    highScoreText.setPosition(1400, 0);
    std::stringstream s;
    s << "High Score:" << highScore;
    highScoreText.setString(s.str());

    // Zombies remaining
    zombiesRemainingText.setFont(font);
    zombiesRemainingText.setCharacterSize(55);
    zombiesRemainingText.setFillColor(Color::White);
    zombiesRemainingText.setPosition(1500, 980);
    zombiesRemainingText.setString("Zombies: 100");

    // Wave number
    waveNumberText.setFont(font);
    waveNumberText.setCharacterSize(55);
    waveNumberText.setFillColor(Color::White);
    waveNumberText.setPosition(1250, 980);
    waveNumberText.setString("Wave: 0");

    // Health bar
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(450, 980);
}


void HUD::setBulletsInClip(int bulletsInClip)
{
    this->bulletsInClip = bulletsInClip;
}


void HUD::setBulletsSpare(int bulletsSpare)
{
    this->bulletsSpare = bulletsSpare;
}


void HUD::setScore(int score)
{
    this->score = score;
}


void HUD::setHighScore(int highScore)
{
    this->highScore = highScore;
}


void HUD::setWave(int wave)
{
    this->wave = wave;
}


void HUD::setNumZombiesAlive(int numZombiesAlive)
{
    this->numZombiesAlive = numZombiesAlive;
}


void HUD::resizeHealthBar(int playerHealth)
{
    healthBar.setSize(Vector2f(playerHealth * 3.f, 70.f));
}


void HUD::update()
{
    // Update the ammo text
    std::stringstream ssAmmo;
    ssAmmo << bulletsInClip << "/" << bulletsSpare;
    ammoText.setString(ssAmmo.str());

    // Update the score text
    std::stringstream ssScore;
    ssScore << "Score:" << score;
    scoreText.setString(ssScore.str());

    // Update the high score text
    std::stringstream ssHiScore;
    ssHiScore << "Hi Score:" << highScore;
    highScoreText.setString(ssHiScore.str());

    // Update the wave
    std::stringstream ssWave;
    ssWave << "Wave:" << wave;
    waveNumberText.setString(ssWave.str());

    // Update the zombies alive text
    std::stringstream ssZombiesAlive;
    ssZombiesAlive << "Zombies:" << numZombiesAlive;
    zombiesRemainingText.setString(ssZombiesAlive.str());
}


void HUD::draw(RenderWindow & window)
{
    window.draw(spriteAmmoIcon);
    window.draw(ammoText);
    window.draw(scoreText);
    window.draw(highScoreText);
    window.draw(healthBar);
    window.draw(waveNumberText);
    window.draw(zombiesRemainingText);
}


void HUD::gameOver(RenderWindow & window)
{
    window.draw(spriteGameOver);
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(highScoreText);
}


void HUD::gamePaused(RenderWindow & window)
{
    window.draw(pausedText);
}


void HUD::gameLevelUp(RenderWindow & window)
{
    window.draw(spriteGameOver);
    window.draw(levelUpText);
}
