#include "stdafx.h"
#include "Background.h"


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
            rVA[currentVertex + 0].position = Vector2f(static_cast<float>(i * TILE_SIZE), static_cast<float>(j * TILE_SIZE));
            rVA[currentVertex + 1].position = Vector2f(static_cast<float>((i * TILE_SIZE) + TILE_SIZE), static_cast<float>(j * TILE_SIZE));
            rVA[currentVertex + 2].position = Vector2f(static_cast<float>((i * TILE_SIZE) + TILE_SIZE), static_cast<float>((j * TILE_SIZE) + TILE_SIZE));
            rVA[currentVertex + 3].position = Vector2f(static_cast<float>((i * TILE_SIZE)), static_cast<float>((j * TILE_SIZE) + TILE_SIZE));

            // Is it a border of the game level?
            if (i == 0 || i == worldWidght - 1 || j == 0 || j == worldHeight - 1)
            {
                rVA[currentVertex + 0].texCoords = Vector2f(0.0f, static_cast<float>(0.0f + TILE_TYPES * TILE_SIZE));
                rVA[currentVertex + 1].texCoords = Vector2f(static_cast<float>(TILE_SIZE), static_cast<float>(0.0f + TILE_TYPES * TILE_SIZE));
                rVA[currentVertex + 2].texCoords = Vector2f(static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE + TILE_TYPES * TILE_SIZE));
                rVA[currentVertex + 3].texCoords = Vector2f(0.0f, static_cast<float>(TILE_SIZE + TILE_TYPES * TILE_SIZE));
            }
            // Otherwise use a random texture for the current quad
            else
            {
                srand(static_cast<int>(time(NULL)) + i *j - i);
                int groundTexture = rand() % TILE_TYPES;
                int textureVerticalOffset = groundTexture * TILE_SIZE;

                rVA[currentVertex + 0].texCoords = Vector2f(0.0f, static_cast<float>(0.0f + textureVerticalOffset));
                rVA[currentVertex + 1].texCoords = Vector2f(static_cast<float>(TILE_SIZE), static_cast<float>(0.f + textureVerticalOffset));
                rVA[currentVertex + 2].texCoords = Vector2f(static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE + textureVerticalOffset));
                rVA[currentVertex + 3].texCoords = Vector2f(0.0f, static_cast<float>(TILE_SIZE + textureVerticalOffset));
            }

            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }

    return TILE_SIZE;
}
