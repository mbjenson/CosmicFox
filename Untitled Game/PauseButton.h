#pragma once
#include <SFML/Graphics.hpp>

class PauseButton
{
public:
	PauseButton();
	int init();
	int update(sf::RenderWindow& win);

	sf::Texture bTex;
	sf::Sprite ps;
	
};

