#pragma once
#include <SFML/Graphics.hpp>

class HudBar
{
public:
	HudBar(sf::Texture& iconTex, sf::Vector2f _screenPos);
	// updates the position of the bar with the corner of the screen
	void render(sf::RenderWindow& win, int quantity, sf::Vector2f cc, sf::Vector2f cs);
	
private:
	void update(sf::Vector2f, sf::Vector2f);
	sf::Sprite hSprite;
	sf::Vector2f screenPos;
};

