#pragma once

#include <SFML/Graphics.hpp>

// Screen
const unsigned ScreenWidth = 1024;
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

// Player movement

const float PlayerSpeed = 400.f;

const sf::Color HeaderTextColor = sf::Color(227, 203, 66);
const sf::Color GroundColor = sf::Color(21, 71, 35);