#pragma once
#include <SFML/Graphics.hpp>

/*
* basic hud element class
* contains an image, position, and other functionality for the hud item
*/
class HudBar
{
public:
	HudBar(sf::Texture& iconTex, sf::Vector2f _screenPos, int initQuan, sf::Vector2u _texSize);
	// updates the position of the bar with the corner of the screen
	void render(sf::RenderWindow& win, int quantity, sf::Vector2f topLeft);
	

	void update(sf::Vector2f, sf::Vector2f);
	sf::Sprite hSprite;
	sf::Vector2f screenPos;
	int initQuanitity;
	sf::Vector2u texSize;
};

