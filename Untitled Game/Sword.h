#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>

class Sword : public Animation
{
	// this will contain the necessary code for a sword in the game
public:
	Sword(float _radius, sf::Vector2f _drawOffSet, sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime);
	Sword();
	sf::CircleShape circleHBox;
	//sf::ConvexShape hBox;
	// this box cuts the circle hit box in half so it is properly the size of the sword swing. I cheated
	sf::RectangleShape notBox;
	void initSword();
	void initSwordOld();
	bool checkHit(sf::FloatRect);
	// returns true if the swing is successful
	bool swing(sf::RenderWindow& win);
	void updatePos(sf::Vector2f playerPos);
	void rotate(sf::RenderWindow& win);
	bool check();

private:
	sf::Clock swordTimer;
	float curAngle = 0;
	int cooldown = 300;
	int swingTime = 120;
	int damage = 1;
	float radius;
	sf::Vector2f drawOffSet;
	bool containsPoint(sf::Vector2f point);
	// a reference to a level here so that I can create a check function that checks if the sword is hitting any enemies
	
	// initialize hitbox with shape and origin, (not for game loop)    
	
	
	// place hitbox in world (get player location and position of mouse and what not)
	


	// check for intersections with enemies

	// update the animation of the sword

	// put the sword away
	
	
	

};

