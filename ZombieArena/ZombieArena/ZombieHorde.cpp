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
                x = minX;
                y = (rand() % maxY) + minY;
                break;
            // Right
            case 1:
                x = maxX;
                y = (rand() % maxY) + minY;
                break;
            // Top
            case 2:
                x = (rand() % maxX) + minX;
                y = minY;
                break;
            // Bottom
            case 3:    
                x = (rand() % maxX) + minX;
                y = maxY;
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
