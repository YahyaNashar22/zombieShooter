#include "Player.hpp"

Player::Player()
    : m_speed(START_SPEED), m_health(START_HEALTH), m_maxHealth(START_HEALTH),
      m_texture("graphics/player.png"), m_sprite(m_texture)
{
    // set the origin to center
    m_sprite.setOrigin({25, 25});
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
    // place the player in the middle
    m_position.x = arena.size.x / 2;
    m_position.y = arena.size.y / 2;

    // copy the details of the arena
    // to the player's m_arena
    m_arena.size.x     = arena.size.x;
    m_arena.size.y     = arena.size.y;
    m_arena.position.x = arena.position.x;
    m_arena.position.y = arena.position.y;
    m_tileSize         = tileSize;

    // store resolution for future use
    m_resolution.x = resolution.x;
    m_resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
    m_speed     = START_SPEED;
    m_health    = START_HEALTH;
    m_maxHealth = START_HEALTH;
}

sf::Time Player::getLastHitTime() { return m_lastHit; }

bool Player::hit(sf::Time timeHit)
{
    if (timeHit.asMicroseconds() - m_lastHit.asMicroseconds() > 200)
    {
        m_lastHit  = timeHit;
        m_health  -= 10;
        return true;
    }
    else
    {
        return false;
    }
}

sf::FloatRect Player::getPosition() { return m_sprite.getGlobalBounds(); }

sf::Vector2f Player::getCenter() { return m_position; }

sf::Angle Player::getRotation() { return m_sprite.getRotation(); }

sf::Sprite Player::getSprite() { return m_sprite; }

int Player::getHealth() { return m_health; }
