#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>

class Sword : public Animation
{
	// this will contain the necessary code for a sword in the game
public:
	Sword(float _radius, sf::Vector2f _drawOffSet, sf::Texture& texSheet, sf::Vector2u texDim,
		int rowLen, int rowNum, float animTime, int cooldown, int swingtime, int damage);
	Sword();
	sf::CircleShape circleHBox;
	// this box cuts the circle hit box in half so it is properly the size of the sword swing. I cheated
	sf::RectangleShape notBox;
	void initSword();
	bool checkHit(sf::FloatRect);
	// returns true if the swing is successful
	bool swing(sf::RenderWindow& win);
	bool swing(sf::Vector2f playerPos);
	void updatePos(sf::Vector2f playerPos);
	void rotate(sf::RenderWindow& win);
	void rotate(sf::Vector2f);
	bool check();

	sf::Clock swordTimer;
	float curAngle = 0;
	//int cooldown = 400; // put these in constructor so different for everyone
	int cooldown;
	// cooldonnw = 300;
	//int swingTime = 120;
	int swingTime;
	//int damage = 1;
	int damage;
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

