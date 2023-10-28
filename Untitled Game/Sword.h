#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>

/*
* Sword class
* contains the necessary functionlity for the player to wield a 
*/
class Sword : public Animation
{
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
	/*
	* performs a sword swing by playing the animation and loading in the hitbox and checking for collision
	*/
	bool swing(sf::RenderWindow& win);
	bool swing(sf::Vector2f playerPos);
	/*
	* update function called by player's update function to ensure the locatino of the sword is the same to the player
	*/
	void updatePos(sf::Vector2f playerPos);
	/*
	* helper function for updatePos
	* updates the rotation of the sword
	*/
	void rotate(sf::RenderWindow& win);
	void rotate(sf::Vector2f);
	/*
	* checks the swords status
	*/
	bool check();

	sf::Clock swordTimer;
	float curAngle = 0;
	int cooldown;
	int swingTime;
	int damage;
	float radius;
	sf::Vector2f drawOffSet;
	bool containsPoint(sf::Vector2f point);
};

