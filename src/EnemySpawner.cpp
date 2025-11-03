#include "EnemySpawner.h"
#include "entities/Enemy.h"

EnemySpawner::EnemySpawner()
{
	// PANU: Is this needed?
}

void EnemySpawner::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& m_enemies)
{
    if (m_spawnClock.getElapsedTime().asSeconds() >= m_enemySpawnInterval)
    {
        std::unique_ptr<Enemy> pEnemy = std::make_unique<Enemy>();
        pEnemy->setPosition(sf::Vector2f(ScreenWidth, GroundLevel));
        if (pEnemy->init())
            m_enemies.push_back(std::move(pEnemy));

		m_enemyCount++;
		m_spawnClock.restart();

		if (m_enemyCount % EnemySpawnUpdateLimit == 0 && m_enemySpawnInterval > EnemyMinSpawnInterval)
		{
			m_enemySpawnInterval -= 0.2f;
			if (m_enemySpawnInterval < EnemyMinSpawnInterval)
				m_enemySpawnInterval = EnemyMinSpawnInterval;
		}
	}

}
