#pragma once

#include <SFML/Graphics.hpp>

// Screen
const unsigned ScreenWidth = 1400;
const unsigned ScreenHeight = 1024;

// Text utils
const unsigned HeaderTextSize = 70;

// Environment
const float GroundLevel = 800.0f;

// Normal jumping
const float PlayerJumpPower = -700.f;
const float Gravity = 800.f;

// Turbo jump
const float TurboJumpLoadTime = 0.8f;
const float TurboJumpEffectTime = 0.4f;
const float TurboJumpPower = -800.f;
const float TurboJumpBarLength = 100.f;

// Meteor Attack
const float MeteorAttackSpeed = 1300.f;

// Dash
const float DashSpeed = 1200.f;
const float DashEffectTime = 0.2f;
const float DashCooldown = 1.0f;

// Player movement
const float PlayerSpeed = 400.f;

// Enemy movement
const float GroundEnemyBaseSpeed = 200.f;
const float AirEnemyBaseSpeed = 300.f;
const float EnemySpeedAddition = 50.f;
const float EnemyMaxSpeedAddition = 1000.f;

// Enemy Spawning
const float EnemyInitSpawnInterval = 2.0f;
const float EnemyMinSpawnInterval = 0.3f;
const float EnemyMinSpawnHeight = GroundLevel;
const float EnemyMaxSpawnHeight = 100.f;
const int EnemySpawnUpdateLimit = 7;

// Colors
const sf::Color HeaderTextColor = sf::Color(227, 203, 66);
const sf::Color GroundColor = sf::Color(21, 71, 35);
const sf::Color PlayerDashColor = sf::Color(250, 99, 35);
const sf::Color PlayerDashCooldownColor = sf::Color(148, 79, 6);