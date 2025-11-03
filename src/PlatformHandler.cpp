#include "PlatformHandler.h"
#include "entities/Player.h"
#include "utils.h"

#include <iostream>

void PlatformHandler::spawnPlatform()
{

	float platformX = ScreenWidth;
	float platformY = randomFloat(m_platformHeightLimits.first, m_platformHeightLimits.second);
	float platformSizeX = randomFloat(m_platformLengthLimits.first, m_platformLengthLimits.second);
	float platformSizeY = PlatformHeight;

	m_platformVec.push_back(Platform({platformX, platformY}, {platformSizeX, platformSizeY}, PlatformSpeed));

}

bool PlatformHandler::isPlatformOOB(Platform& platform)
{
	sf::FloatRect bounds = platform.getShape().getGlobalBounds();

	if (bounds.position.x + bounds.size.x < 0)
		return true;

	return false;
}


void PlatformHandler::update(float dt, Player* player)
{
	size_t i = 0;
	while (i < m_platformVec.size())
	{
		m_platformVec[i].update(dt);
		if (isPlatformOOB(m_platformVec[i]))
		{
			std::swap(m_platformVec[i], m_platformVec.back());
			m_platformVec.pop_back();
			continue;
		}
	
		if (m_platformVec[i].checkHasPlayer() && m_platformVec[i].isPlayerOOB(player))
		{
			player->removeFromPlatform();
			m_platformVec[i].setHasPlayer(false);
		}

		i++;
	}

	if (m_spawnClock.getElapsedTime().asSeconds() < m_spawnTime)
		return ;

	spawnPlatform();
	m_spawnClock.restart();
	
}


void PlatformHandler::draw(sf::RenderTarget& target)
{
	for (auto& platform : m_platformVec)
	{
		platform.draw(target);
	}
}

void PlatformHandler::resolvePlayerCollison(int idx, Player* player)
{
	sf::Vector2f prevPos = player->getPrevPosition();
	float playerRadius = player->getSize().x;
	float playerPrevBottom = prevPos.y + playerRadius;
	float playerPrevTop = prevPos.y - playerRadius;
	float playerPrevLeft = prevPos.x - playerRadius;
	float playerPrevRight = prevPos.x + playerRadius;

	sf::FloatRect platformBounds = m_platformVec[idx].getShape().getGlobalBounds();
	float platformTop = platformBounds.position.y;
	float platformBottom = platformBounds.position.y + platformBounds.size.y;
	float platformLeft = platformBounds.position.x;
	float platformRight = platformBounds.position.x + platformBounds.size.x;

	if (playerPrevBottom < platformTop)
	{
		player->setOnPlatform(platformTop - playerRadius - 10.f, idx); // PANU: Check this
		m_platformVec[idx].setHasPlayer(true);
	}
	else
	{ /*
		if (playerPrevTop > platformBottom)
		{
			player->setPosition({playerPrevLeft + PlayerShapeRadius, playerPrevTop + PlayerShapeRadius});
			player->setVelocity({0, 20});
			player->setIsJumping(true); // Player is affected by gravity

		}
		else if (playerPrevLeft > platformRight && !player->getIsDownDashing())
		{
			player->setPosition({platformRight + PlayerShapeRadius, player->getCurPos().y});
			player->setPlatformCollision(true);
			player->setVelocity({20, 0});
		}
		else if (playerPrevRight < platformLeft && !player->getIsDownDashing())
		{
			player->setPosition({platformLeft - PlayerShapeRadius, player->getCurPos().y});
			player->setPlatformCollision(true);
			player->setVelocity({-20, 0});
		} */
	}
	
}

void PlatformHandler::checkPlayerCollision(Player* player)
{
	sf::FloatRect playerBounds = player->getGlobalBounds();

	for (size_t i = 0; i < m_platformVec.size(); ++i)
	{
		if (checkRectCollision(playerBounds, m_platformVec[i].getShape().getGlobalBounds()))
		{
			resolvePlayerCollison(i, player);
			return ;
		}
	}
}