#pragma once
#include <SFML/Graphics.hpp>
/*
* This contains all the necessary code to open a menu in the game
* includes code for buttons and other things like that 
*/
class Menu
{
public:
	Menu();
	int init();
	int update(sf::RenderWindow& win);

	sf::Texture titleTex;
	sf::Sprite title;

	sf::Texture playBTex;
	sf::Texture quitBTex;
	sf::Sprite playB;
	sf::Sprite quitB;

	sf::Texture bgTex;
	sf::Sprite bg;
};

