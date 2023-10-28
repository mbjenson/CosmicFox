#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

// top-down view camera class.
// inherits basic functionality from sf::View class
/*
* Camera class
* defines a view which smoothly follows the player around the level
*/
class Camera : public sf::View
{
public:
	using sf::View::View;
	/*
	* update the camera position with respect to the player
	*/
	void update(Player& player1, float deltaTime, sf::Vector2f mapSize);
	
	sf::Vector2f target;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f distance;
	float lag = 5.5;

};

