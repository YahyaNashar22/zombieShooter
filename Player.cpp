#include "Player.hpp"
#include <cmath>

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

void Player::moveLeft() { m_leftPressed = true; }
void Player::moveRight() { m_rightPressed = true; }
void Player::moveUp() { m_upPressed = true; }
void Player::moveDown() { m_downPressed = true; }

void Player::stopLeft() { m_leftPressed = false; }
void Player::stopRight() { m_rightPressed = false; }
void Player::stopUp() { m_upPressed = false; }
void Player::stopDown() { m_downPressed = false; }

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
    if (m_upPressed)
    {
        m_position.y -= m_speed * elapsedTime;
    }
    if (m_downPressed)
    {
        m_position.y += m_speed * elapsedTime;
    }
    if (m_rightPressed)
    {
        m_position.x += m_speed * elapsedTime;
    }
    if (m_leftPressed)
    {
        m_position.x -= m_speed * elapsedTime;
    }

    m_sprite.setPosition(m_position);

    // keep player in the arena
    // Left
    if (m_position.x < m_arena.position.x)
    {
        m_position.x = m_arena.position.x;
    }

    // Right
    if (m_position.x > m_arena.position.x + m_arena.size.x - m_tileSize)
    {
        m_position.x = m_arena.position.x + m_arena.size.x - m_tileSize;
    }

    // Top
    if (m_position.y < m_arena.position.y)
    {
        m_position.y = m_arena.position.y;
    }

    // Bottom
    if (m_position.y > m_arena.position.y + m_arena.size.y - m_tileSize)
    {
        m_position.y = m_arena.position.y + m_arena.size.y - m_tileSize;
    }

    // calculate the angle the player is facing
    float radians = std::atan2(mousePosition.y - m_resolution.y / 2.f,
                               mousePosition.x - m_resolution.x / 2.f);

    m_sprite.setRotation(sf::radians(radians));
}

void Player::upgradeSpeed() { m_speed += (START_SPEED * .2f); }

void Player::upgradeHealth() { m_maxHealth += (START_HEALTH * .2f); }

void Player::increaseHealthLevel(int amount)
{
    m_health += amount;
    if (m_health > m_maxHealth)
    {
        m_health = m_maxHealth;
    }
}
