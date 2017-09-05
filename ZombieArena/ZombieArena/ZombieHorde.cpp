#include "stdafx.h"
#include "ZombieHorde.h"


Zombie* createHorde(int numZombies, IntRect arena)
{
    Zombie* zombies = new Zombie[numZombies];

    int maxY = arena.height - 20;
    int minY = arena.top + 20;
    int maxX = arena.width - 20;
    int minX = arena.left + 20;

    for (int i = 0; i < numZombies; ++i)
    {
        // Choosing the side, where should the zombie spawn
        srand((int)time(0) * i);
        int side = (rand() % 4);
        float x, y;

        switch (side)
        {
            // Left
            case 0:
                x = static_cast<float>(minX);
                y = static_cast<float>((rand() % maxY) + minY);
                break;
            // Right
            case 1:
                x = static_cast<float>(maxX);
                y = static_cast<float>((rand() % maxY) + minY);
                break;
            // Top
            case 2:
                x = static_cast<float>((rand() % maxX) + minX);
                y = static_cast<float>(minY);
                break;
            // Bottom
            case 3:    
                x = static_cast<float>((rand() % maxX) + minX);
                y = static_cast<float>(maxY);
                break;
        }

        // Randomly select the zombie type
        srand((int)time(0) * i * 2);
        int type = (rand() % 3);

        // And spawn it on the game level
        zombies[i].spawn(x, y, type, i);
    }

    return zombies;
}
