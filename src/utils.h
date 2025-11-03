#pragma once

#include <SFML/Graphics.hpp> // PANU: Add onlt what you need
#include "Constants.h"

void drawHeaderText(const sf::Font* font, sf::RenderTarget& target, std::string str);
bool checkRectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
void handleCameraShake(sf::RenderTarget& target);
float randomFloat(float min, float max);