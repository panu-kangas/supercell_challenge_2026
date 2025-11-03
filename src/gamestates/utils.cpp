#include <SFML/Graphics.hpp>
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