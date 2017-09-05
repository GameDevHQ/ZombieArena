#include "stdafx.h"
#include "Player.h"
#include "Utils.h"


int createBackground(VertexArray& rVA, IntRect arena)
{
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;

    int worldWidght = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;

    // Resize the arena background to an appropriate sizee and make it with quads 
    rVA.setPrimitiveType(Quads);
    rVA.resize(worldWidght * worldHeight * VERTS_IN_QUAD);
    
    // Start of the beginning
    int currentVertex = 0;


    for (int i = 0; i < worldWidght; ++i)
    {
        for (int j = 0; j < worldHeight; ++j)
        {
            // Specify sprite position on the game level
            rVA[currentVertex + 0].position = Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            rVA[currentVertex + 1].position = Vector2f((i * TILE_SIZE) + TILE_SIZE, j * TILE_SIZE);
            rVA[currentVertex + 2].position = Vector2f((i * TILE_SIZE) + TILE_SIZE, (j * TILE_SIZE) + TILE_SIZE);
            rVA[currentVertex + 3].position = Vector2f((i * TILE_SIZE), (j * TILE_SIZE) + TILE_SIZE);
        
            // Is it a border of the game level?
            if (i == 0 || i == worldWidght - 1 || j == 0 || j == worldHeight - 1)
            {
                rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
            }
            // Otherwise use a random texture for the current quad
            else
            {
                srand(static_cast<int>(time(NULL)) + i *j - i);
                int groundTexture = rand() % TILE_TYPES;
                int textureVerticalOffset = groundTexture * TILE_SIZE;

                rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + textureVerticalOffset);
                rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + textureVerticalOffset);
                rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + textureVerticalOffset);
                rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + textureVerticalOffset);
            }

            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }

    return TILE_SIZE;
}


int main()
{
    // Starts with the GAME_OVER state
    GameState state = GameState::GAME_OVER;

    // Get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    // Create a window in a fullscreen mode
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

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
    Texture textureBackground;
    textureBackground.loadFromFile("Resources/Graphics/background_sheet.png");

    // The boundaries of the arena
    IntRect arena;

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

            // Update the player
            player.update(dtAsSeconds, Mouse::getPosition());

            // Make a note of the players new position
            Vector2f playerPosition(player.getCenter());

            // Make the view centre around the player				
            mainView.setCenter(player.getCenter());
        }

        //--------------------------------------------------
        // Draw the scene
        //--------------------------------------------------

        if (state == GameState::PLAYING)
        {
            window.clear();

            // Set the mainView to be displayed in the window and draw related to it
            window.setView(mainView);
            window.draw(background, &textureBackground);
            window.draw(player.getSprite());
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

    return 0;
}
