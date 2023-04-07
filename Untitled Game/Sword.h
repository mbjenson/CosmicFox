#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>

class Sword : public Animation
{
	// this will contain the necessary code for a sword in the game
public:
	Sword(sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime);
	Sword();
	sf::ConvexShape hBox;
	void initSword();
	// returns true if the swing is successful
	bool swing(sf::RenderWindow& win);
	void updatePos(sf::Vector2f playerPos);
	void rotate(sf::RenderWindow& win);
	bool check();

private:
	sf::Clock swordTimer;
	float curAngle;
	int cooldown = 300;
	int swingTime = 120;
	int damage = 1;
	// a reference to a level here so that I can create a check function that checks if the sword is hitting any enemies
	
	// initialize hitbox with shape and origin, (not for game loop)    
	
	
	// place hitbox in world (get player location and position of mouse and what not)
	


	// check for intersections with enemies

	// update the animation of the sword

	// put the sword away
	
	
	

};

