#include "ZombieArena.hpp"

int createBackground(sf::VertexArray &rVA, sf::IntRect arena)
{
    const int TILE_SIZE     = 50;
    const int TILE_TYPES    = 3;
    const int VERTS_IN_QUAD = 4;

    int worldWidth  = arena.size.x / TILE_SIZE;
    int worldHeight = arena.size.y / TILE_SIZE;

    rVA.setPrimitiveType(sf::PrimitiveType::Triangles);

    // set the size of the vertex array
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    // start at the beginning of the vertex array
    int currentVertex = 0;
    return TILE_SIZE;
}