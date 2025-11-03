#include "StatePlaying.h"
#include "StatePaused.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <memory>
#include <iostream>
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

StatePlaying::StatePlaying(StateStack& stateStack)
    : m_stateStack(stateStack)
{
}

bool StatePlaying::init()
{
    m_ground.setSize({ScreenWidth, 256.0f});
    m_ground.setPosition({0.0f, GroundLevel});
    m_ground.setFillColor(GroundColor);

    m_pPlayer = std::make_unique<Player>();
    if (!m_pPlayer || !m_pPlayer->init())
        return false;

    m_pPlayer->setPosition(sf::Vector2f(200, GroundLevel));

	m_pEnemySpawner = std::make_unique<EnemySpawner>();
	if (!m_pEnemySpawner)
		return false;

    return true;
}

void StatePlaying::checkEnemyCollisionAndOOB()
{
	if (m_enemies.empty())
		return ;

    bool playerDied = false;
	float leftBoundary = 0.0f - m_enemies[0]->getCollisionRadius();
	size_t i = 0;
    while (i < m_enemies.size())
    {
		if (m_enemies[i]->getPosition().x <= leftBoundary)
		{
			std::swap(m_enemies[i], m_enemies.back());
			m_enemies.pop_back();
			continue;
		}

        float distance = (m_pPlayer->getPosition() - m_enemies[i]->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + m_enemies[i]->getCollisionRadius(), 2.0f);
        // const sf::Vector2f playerPosition = m_pPlayer->getPosition(); --> PANU: Why?

        if (distance <= minDistance)
        {
			if (m_pPlayer->isDashing())
			{
				std::swap(m_enemies[i], m_enemies.back());
				m_enemies.pop_back();
				m_pPlayer->resetDash();
				continue;
			}
			else
			{
				playerDied = true;
				break;
			}
        }

		i++;
    }

    if (playerDied)
        m_stateStack.popDeferred();
}

void StatePlaying::update(float dt)
{
	m_pEnemySpawner->spawnEnemy(m_enemies);

    bool isPauseKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    m_hasPauseKeyBeenReleased |= !isPauseKeyPressed;
    if (m_hasPauseKeyBeenReleased && isPauseKeyPressed)
    {
        m_hasPauseKeyBeenReleased = false;
        m_stateStack.push<StatePaused>();
    }

    m_pPlayer->update(dt);

    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
    {
        pEnemy->update(dt);
    }

	checkEnemyCollisionAndOOB();
}

void StatePlaying::render(sf::RenderTarget& target) const
{
    target.draw(m_ground);
    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
        pEnemy->render(target);
    m_pPlayer->render(target);
}
