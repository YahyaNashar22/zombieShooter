#pragma once

#include <SFML/Graphics.hpp>

class Player
{
    const float START_SPEED  = 200;
    const float START_HEALTH = 100;

    sf::Vector2f m_position;

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    // scrn resolution
    sf::Vector2f m_resolution;

    // size of the current arena
    sf::IntRect m_arena;

    // size of each tile size of arena
    int m_tileSize;

    // directions
    bool m_upPressed;
    bool m_downPressed;
    bool m_leftPressed;
    bool m_rightPressed;

    int m_health;
    int m_maxHealth;

    // when was the player last hit
    sf::Time m_lastHit;

    float m_speed;

  public:
    Player();

    void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);

    // call this at the end of every game
    void resetPlayerStats();

    // handle getting hit
    bool hit(sf::Time timeHit);

    // how long ago got hit
    sf::Time getLastHitTime();

    sf::FloatRect getPosition();

    sf::Vector2f getCenter();

    float getRotation();

    sf::Sprite getSprite();

    // movements
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // stop movements
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    // called every frame
    void update(float elapsedTime, sf::Vector2i mousePosition);

    // speed boost
    void upgradeSpeed();

    // add health
    void upgradeHealth();

    // increase maxHealth
    void increaseHealthLevel(int amount);

    int getHealth();
};