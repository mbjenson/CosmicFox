#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

class Sword : public Animation
{
	// this will contain the necessary code for a sword in the game
public:
	Sword(Player& player, sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime);
	Sword();
	void swing(float angle);
	void initSword();
	sf::ConvexShape hBox;
	void loadHitBox();
	void update();
private:
	sf::Clock swordTimer;
	
	int cooldown = 500;
	int swingTime = 300;
	int damage = 1;
	Player* player;
	
	// initialize hitbox with shape and origin, (not for game loop)    
	
	
	// place hitbox in world (get player location and position of mouse and what not)
	


	// check for intersections with enemies

	// update the animation of the sword

	// put the sword away
	
	
	

};

