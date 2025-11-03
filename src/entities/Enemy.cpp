#include "Enemy.h"
#include "ResourceManager.h"
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>


bool Enemy::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("enemy.png"); // PANU: Make enemies round too? Makes collision detection more easy
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_pSprite->setScale(sf::Vector2f(2.5f, 2.5f));
    m_collisionRadius = collisionRadius;

    return true;
}

void Enemy::update(float dt)
{
    m_position.x -= 200 * dt;
}

void Enemy::render(sf::RenderTarget& target) const
{
    m_pSprite->setPosition(m_position);
    target.draw(*m_pSprite);

	// PANU: For testing only
	sf::CircleShape collisionShape;
	collisionShape.setRadius(collisionRadius);
	collisionShape.setFillColor(sf::Color(0, 120, 0, 128));
	sf::FloatRect localBounds = collisionShape.getLocalBounds();
    collisionShape.setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
	collisionShape.setPosition(m_position);

	target.draw(collisionShape);
}
