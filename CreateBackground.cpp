#include "ZombieArena.hpp"

#include <cstdlib>
#include <ctime>

int createBackground(sf::VertexArray &rVA, sf::IntRect arena)
{
    const int TILE_SIZE     = 50;
    const int TILE_TYPES    = 3;
    const int VERTS_IN_TILE = 6;

    int worldWidth  = arena.size.x / TILE_SIZE;
    int worldHeight = arena.size.y / TILE_SIZE;

    // SFML 3 removed Quads, so each tile is made from 2 triangles
    rVA.setPrimitiveType(sf::PrimitiveType::Triangles);

    // 6 vertices per tile
    rVA.resize(worldWidth * worldHeight * VERTS_IN_TILE);

    int currentVertex = 0;

    // Seed random generator once
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int w = 0; w < worldWidth; w++)
    {
        for (int h = 0; h < worldHeight; h++)
        {
            float left   = static_cast<float>(w * TILE_SIZE);
            float top    = static_cast<float>(h * TILE_SIZE);
            float right  = left + TILE_SIZE;
            float bottom = top + TILE_SIZE;

            // ---------------------------
            // Vertex positions
            // ---------------------------

            // Triangle 1
            rVA[currentVertex + 0].position = sf::Vector2f(left, top);
            rVA[currentVertex + 1].position = sf::Vector2f(right, top);
            rVA[currentVertex + 2].position = sf::Vector2f(right, bottom);

            // Triangle 2
            rVA[currentVertex + 3].position = sf::Vector2f(left, top);
            rVA[currentVertex + 4].position = sf::Vector2f(right, bottom);
            rVA[currentVertex + 5].position = sf::Vector2f(left, bottom);

            int verticalOffset;

            // Border tile = wall
            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
            {
                verticalOffset = TILE_TYPES * TILE_SIZE;
            }
            else
            {
                // Random grass / floor tile
                int tileType   = std::rand() % TILE_TYPES;
                verticalOffset = tileType * TILE_SIZE;
            }

            float textureTop = static_cast<float>(verticalOffset);
            float textureBottom =
                static_cast<float>(verticalOffset + TILE_SIZE);

            float textureLeft  = 0.f;
            float textureRight = static_cast<float>(TILE_SIZE);

            // ---------------------------
            // Texture coordinates
            // ---------------------------

            // Triangle 1
            rVA[currentVertex + 0].texCoords =
                sf::Vector2f(textureLeft, textureTop);

            rVA[currentVertex + 1].texCoords =
                sf::Vector2f(textureRight, textureTop);

            rVA[currentVertex + 2].texCoords =
                sf::Vector2f(textureRight, textureBottom);

            // Triangle 2
            rVA[currentVertex + 3].texCoords =
                sf::Vector2f(textureLeft, textureTop);

            rVA[currentVertex + 4].texCoords =
                sf::Vector2f(textureRight, textureBottom);

            rVA[currentVertex + 5].texCoords =
                sf::Vector2f(textureLeft, textureBottom);

            currentVertex += VERTS_IN_TILE;
        }
    }

    return TILE_SIZE;
}
