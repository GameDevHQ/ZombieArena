#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Background.h"
#include "TextureManager.h"
#include "Pickup.h"
#include "Zombie.h"
#include "ZombieHorde.h"
#include "Utils.h"


int main()
{
    // Starts with the GAME_OVER state
    GameState state = GameState::GAME_OVER;

    // Get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = static_cast<float>(VideoMode::getDesktopMode().width);
    resolution.y = static_cast<float>(VideoMode::getDesktopMode().height);

    // Create a window in a fullscreen mode
    RenderWindow window(
        VideoMode(static_cast<unsigned int>(resolution.x), static_cast<unsigned int>(resolution.y)),
        "Zombie Arena", Style::Fullscreen
    );

    // Create a an SFML View for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
    
    // Main clock for timing everything
    Clock clock;

    // Tracking the current game session
    Time gameTimeTotal;

    // Where is the mouse in relation to world coordinates
    Vector2f mouseWorldPosition;

    // Where is the mouse in relation to screen coordinates
    Vector2i mouseScreenPosition;

    // Create an instance of the Player class
    Player player;

    // Create a game level background
    VertexArray background;
    Texture textureBackground = TextureManager::getInstance().getTexture("Resources/Graphics/background_sheet.png");

    // Monsters on the level
    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;

    // Track the fired bullet by the player
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1.0f;
    Time lastPressedFireButton;

    // The boundaries of the arena
    IntRect arena;

    // Replace the default cursor on the custom
    window.setMouseCursorVisible(false);
    Sprite spriteCrosshair = Sprite(TextureManager::getInstance().getTexture("Resources/Graphics/crosshair.png"));
    spriteCrosshair.setOrigin(25, 25);

    // Create a couple of pickups
    Pickup healthPickup(1);
    Pickup ammoPickup(2);

    // The main game loop
    while (window.isOpen())
    {
        //--------------------------------------------------
        // Handle the players input
        //--------------------------------------------------
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                // Pause a game while playing
                if (event.key.code == Keyboard::Return &&
                    state == GameState::PLAYING)
                {
                    state = GameState::PAUSED;
                }
                // Restart while paused
                else if (event.key.code == Keyboard::Return && state == GameState::PAUSED)
                {
                    state = GameState::PLAYING;
                    // Don't accumulate the time while game at pause...
                    clock.restart();
                }
                // Start a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return && state == GameState::GAME_OVER)
                {
                    state = GameState::LEVELING_UP;
                }

                if (state == GameState::PLAYING)
                {
                    // Reload the weapon
                    if (event.key.code == Keyboard::R)
                    {
                        if (bulletsSpare >= clipSize)
                        {
                            bulletsInClip = clipSize;
                            bulletsSpare -= clipSize;
                        }
                        else if (bulletsSpare > 0)
                        {
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                        }
                        else
                        {
                        }
                    }
                }
            }
        }

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle the player movement (WASD keys)
        if (state == GameState::PLAYING)
        {
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }

            // Fire a bullet
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if ((gameTimeTotal.asMilliseconds() - lastPressedFireButton.asMilliseconds() > 1000 / fireRate) && bulletsInClip > 0)
                {
                    Vector2f playerPosition = player.getCenter();
                    bullets[currentBullet].shoot(playerPosition.x, playerPosition.y, mouseWorldPosition.x, mouseWorldPosition.y);
                    
                    // Reserve the next position for the future shots
                    currentBullet++;
                    currentBullet %= currentBullet % 100;

                    // Update a time, when the left mouse button was clicked
                    lastPressedFireButton = gameTimeTotal;
                    // Reduce the count of bullets in the clip
                    bulletsInClip--;
                }
            }
        }

        // Handle the player is leveling up
        if (state == GameState::LEVELING_UP)
        { 
            if (event.key.code == Keyboard::Num1)
            {
                state = GameState::PLAYING;
            }

            if (event.key.code == Keyboard::Num2)
            {
                state = GameState::PLAYING;
            }

            if (event.key.code == Keyboard::Num3)
            {
                state = GameState::PLAYING;
            }

            if (event.key.code == Keyboard::Num4)
            {
                state = GameState::PLAYING;
            }

            if (event.key.code == Keyboard::Num5)
            {
                state = GameState::PLAYING;
            }

            if (event.key.code == Keyboard::Num6)
            {
                state = GameState::PLAYING;
            }

            if (state == GameState::PLAYING)
            {
                // Prepare the game level
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                // Initialize the game level...
                int tileSize = createBackground(background, arena);

                // Spawn the player in the middle of the arena
                player.spawn(arena, resolution, tileSize);

                // Configure the pickups
                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);

                // Delete the previously allocated memory (if it exists)
                delete[] zombies;
                // And create a new horde of zombies
                numZombies = 10;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;

                // Reset the clock at the start of the game...
                clock.restart();
            }
        }

        //--------------------------------------------------
        // Update the scene
        //--------------------------------------------------
        
        if (state == GameState::PLAYING)
        {
            // Update the delta time and accumulate the total game time
            Time timedelta = clock.restart();
            gameTimeTotal += timedelta;
            
            // Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = timedelta.asSeconds();

            // Where is the mouse pointer
            mouseScreenPosition = Mouse::getPosition();
            // And convert mouse position to world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            // Set the position for a custom crosshair
            spriteCrosshair.setPosition(mouseWorldPosition);

            // Update the player
            player.update(dtAsSeconds, Mouse::getPosition());

            // Make a note of the players new position
            Vector2f playerPosition(player.getCenter());

            // Make the view centre around the player				
            mainView.setCenter(player.getCenter());

            // Update each zombie if he is alive
            for (int i = 0; i < numZombies; ++i)
            {
                if (zombies[i].isAlive())
                {
                    zombies[i].update(timedelta.asSeconds(), playerPosition);
                }
            }

            // Update each existing bullet
            for (int i = 0; i < 100; ++i)
            {
                if (bullets[i].isInFlight())
                {
                    bullets[i].update(timedelta.asSeconds());
                }
            }

            // Update the pickups
            healthPickup.update(dtAsSeconds);
            ammoPickup.update(dtAsSeconds);
        }

        //--------------------------------------------------
        // Draw the scene
        //--------------------------------------------------

        if (state == GameState::PLAYING)
        {
            window.clear();

            // Set the mainView to be displayed in the window and draw related to it
            window.setView(mainView);
            
            // Draw the game level
            window.draw(background, &textureBackground);

            // Draw the zombies
            for (int i = 0; i < numZombies; ++i)
            {
                window.draw(zombies[i].getSprite());
            }

            // Draw the bullets
            for (int i = 0; i < 100; ++i)
            {
                if (bullets[i].isInFlight())
                {
                    window.draw(bullets[i].getShape());
                }
            }

            // Draw the pickups, if currently spawned
            if (ammoPickup.isSpawned())
            {
                window.draw(ammoPickup.getSprite());
            }
            if (healthPickup.isSpawned())
            {
                window.draw(healthPickup.getSprite());
            }

            // Draw the player
            window.draw(player.getSprite());

            //Draw the crosshair
            window.draw(spriteCrosshair);
        }

        if (state == GameState::LEVELING_UP)
        {
        }

        if (state == GameState::PAUSED)
        {
        }

        if (state == GameState::GAME_OVER)
        {
        }

        window.display();
    }

    // Delete the previously allocated memory (if it exists)
    delete[] zombies;

    return 0;
}
