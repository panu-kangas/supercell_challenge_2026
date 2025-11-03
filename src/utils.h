#pragma once

#include <SFML/Graphics.hpp> // PANU: Add onlt what you need
#include "Constants.h"

void drawHeaderText(const sf::Font* font, sf::RenderTarget& target, std::string str);
float randomFloat(float min, float max);