#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>

class Sword : public Animation
{
	// this will contain the necessary code for a sword in the game
public:
	Sword(sf::Vector2f origin, sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime);
	void swing(sf::Vector2f dir);
private:
	sf::Clock swordTimer;
	
	sf::VertexArray hitBox = sf::VertexArray(sf::LineStrip, 7);
	int cooldown = 500;
	int swingTime = 300;
	int damage = 1;

	void initHitBox();
	

	

};

