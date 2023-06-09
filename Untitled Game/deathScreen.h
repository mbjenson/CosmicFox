#pragma once
#include <SFML/graphics.hpp>
#include <SFML/audio.hpp>

class deathScreen
{
public:
	deathScreen();
	int init();
	int update(sf::RenderWindow& win);

	sf::Texture deathTex;
	sf::Sprite text;

	sf::Texture playBTex;
	sf::Texture quitBTex;
	sf::Sprite playB;
	sf::Sprite quitB;

	sf::Texture screenTex;
	sf::Sprite screen;
	

	//sf::Music music;

};

