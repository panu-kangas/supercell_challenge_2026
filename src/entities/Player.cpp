#include "Player.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

#include <iostream>

Player::Player()
{
}

bool Player::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("player.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    m_rotation = sf::degrees(0);
    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_pSprite->setScale(sf::Vector2f(3.0f, 3.0f));
    m_collisionRadius = collisionRadius;

    return true;
}

void Player::checkGrounded()
{
	if (m_position.y >= GroundLevel)
	{		
        m_isInAir = false;
		m_velocity.y = 0;
		m_position.y = GroundLevel;
	}
}

void Player::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !m_spaceHold && !m_isInAir)
    {
        m_isInAir = true;
		m_spaceHold = true;
		m_velocity.y = PlayerJumpPower;
    }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		m_spaceHold = false;
	}

	if (m_isInAir)
	{
		if (m_velocity.y < 0)
			m_velocity.y += Gravity * 2.3 * dt;
		else
			m_velocity.y += Gravity * 3.3 * dt;
	}
	else
		m_velocity.y = 0;

	m_position.y += m_velocity.y * dt;
	
    checkGrounded();

}

void Player::render(sf::RenderTarget& target) const
{
    m_pSprite->setRotation(m_rotation);
    m_pSprite->setPosition(m_position);
    target.draw(*m_pSprite);

	// PANU: For testing only
	sf::CircleShape collisionShape;
	collisionShape.setRadius(collisionRadius);
	collisionShape.setFillColor(sf::Color(120, 0, 0, 128));
	sf::FloatRect localBounds = collisionShape.getLocalBounds();
    collisionShape.setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
	collisionShape.setPosition(m_position);

	target.draw(collisionShape);
}
