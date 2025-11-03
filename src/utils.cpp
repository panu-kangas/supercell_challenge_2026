#include <SFML/Graphics.hpp>
#include <random>
#include "Constants.h"

void drawHeaderText(const sf::Font* font, sf::RenderTarget& target, std::string str)
{
	sf::Text text(*font, str);

	text.setFillColor(HeaderTextColor);
	text.setCharacterSize(HeaderTextSize);

	float textX = ScreenWidth / 2 - text.getLocalBounds().size.x / 2;
	float textY = 40.f; 
	text.setPosition({textX, textY});

	target.draw(text);
}

/**
 * 
 * This function came from ChatGPT!!
 * I read a bit about this approach and it seems legit, and gives better output than using just rand()
 * 
 */
float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);
}