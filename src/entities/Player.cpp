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
	m_pSprite->setScale(sf::Vector2f(3.0f, 3.0f));
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_collisionRadius = collisionRadius;

	m_jumpLoadBar.setSize({0, 10});
	m_jumpLoadBar.setFillColor(sf::Color::Red);
	m_jumpLoadBar.setPosition({m_position.x - TurboJumpBarLength / 2, m_position.y - localBounds.size.y - m_jumpLoadBar.getSize().y - 15.f});

    return true;
}

void Player::checkOutOfBounds()
{
	sf::FloatRect localBounds = m_pSprite->getLocalBounds();
	float leftLimit = 0.0f + localBounds.size.x;
	float rightLimit = ScreenWidth - localBounds.size.x;

	if (m_position.x < leftLimit)
		m_position.x = leftLimit;
	else if (m_position.x > rightLimit)
		m_position.x = rightLimit;
}

void Player::checkGrounded()
{
	if (m_position.y >= GroundLevel)
	{		
        m_isInAir = false;
		m_didDoubleJump = false;
		m_velocity.y = 0;
		m_position.y = GroundLevel;
	}
}

void Player::applyGravity(float dt)
{
	if (m_isTurboJumping)
		return ;

	if (m_isInAir)
	{
		if (m_velocity.y < 0)
			m_velocity.y += Gravity * 2.3 * dt;
		else
			m_velocity.y += Gravity * 3.3 * dt;
	}
	else
		m_velocity.y = 0;
}

void Player::handleSideMovement(bool aPressed, bool dPressed)
{
	if (m_isLoadingTurbo)
		return ;

	if ((!aPressed && !dPressed) || (aPressed && dPressed))
		m_velocity.x = 0;
	else if (aPressed)
		m_velocity.x = -1 * m_speed;
	else if (dPressed)
		m_velocity.x = m_speed;
}

void Player::checkTurboJump(bool sPressed)
{
	if (m_isInAir)
		return ;

	if (sPressed && !m_sHold)
	{
		m_sHold = true;
		m_isLoadingTurbo = true;
		m_velocity.x = 0;
		m_turboLoadClock.restart();
	}
}


void Player::checkJumps(bool wPressed)
{
	if (m_isTurboJumping || m_isLoadingTurbo)
		return ;

	if (wPressed && !m_wHold && !m_didDoubleJump && m_velocity.y > PlayerJumpPower + 400.f)
    {
		if (!m_isInAir)
		{
        	m_isInAir = true;
		}
		else
		{
			m_didDoubleJump = true;
		}

		m_wHold = true;
		m_velocity.y = PlayerJumpPower;
    }
}

void Player::handleInput()
{
	bool wPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	checkJumps(wPressed);

	bool aPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	bool dPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	handleSideMovement(aPressed, dPressed);

	bool sPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
	checkTurboJump(sPressed);


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		m_wHold = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (m_isLoadingTurbo)
			m_isLoadingTurbo = false;
		m_sHold = false;
	}
}

void Player::checkTimers()
{
	if (m_isLoadingTurbo && m_turboLoadClock.getElapsedTime().asSeconds() >= TurboJumpLoadTime)
	{
		m_isLoadingTurbo = false;
		m_isTurboJumping = true;
		m_velocity.y = TurboJumpPower;
		m_turboEffectClock.restart();
	}

	if (m_isTurboJumping && m_turboEffectClock.getElapsedTime().asSeconds() >= TurboJumpEffectTime)
	{
		m_isTurboJumping = false;
		m_isInAir = true;
	}
}

void Player::update(float dt)
{
	checkTimers();
	handleInput();
	applyGravity(dt);

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;
	
	checkOutOfBounds();
    checkGrounded();
	updateJumpLoadBar();
}

void Player::updateJumpLoadBar()
{
	if (!m_isLoadingTurbo)
	{
		if (m_jumpLoadBar.getSize().x > 0)
			m_jumpLoadBar.setSize({0, m_jumpLoadBar.getSize().y});
		if (m_jumpLoadBar.getFillColor() != sf::Color::Red)
			m_jumpLoadBar.setFillColor(sf::Color::Red);
		return;
	}
	
	float turboLoadCurTime = m_turboLoadClock.getElapsedTime().asSeconds();
	float barLength = (turboLoadCurTime / TurboJumpLoadTime) * TurboJumpBarLength;
	if (barLength >= TurboJumpBarLength)
	{
		barLength = TurboJumpBarLength;
		m_jumpLoadBar.setFillColor(sf::Color::Green); // PANU: Is this color thing needed?
	}
	m_jumpLoadBar.setSize({barLength, m_jumpLoadBar.getLocalBounds().size.y});
	sf::FloatRect playerBounds = m_pSprite->getLocalBounds();
	m_jumpLoadBar.setPosition({m_position.x - TurboJumpBarLength / 2, m_position.y - playerBounds.size.y - m_jumpLoadBar.getSize().y - 15.f});

}

void Player::render(sf::RenderTarget& target) const
{
    m_pSprite->setRotation(m_rotation);
    m_pSprite->setPosition(m_position);
    target.draw(*m_pSprite);
	target.draw(m_jumpLoadBar);

/*	// PANU: For testing only
	sf::CircleShape collisionShape;
	collisionShape.setRadius(collisionRadius);
	collisionShape.setFillColor(sf::Color(120, 0, 0, 128));
	sf::FloatRect localBounds = collisionShape.getLocalBounds();
    collisionShape.setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
	collisionShape.setPosition(m_position);

	target.draw(collisionShape); */
}
