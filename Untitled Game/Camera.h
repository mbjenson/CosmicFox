#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Camera : public sf::View
{
public:
	using sf::View::View;
	void update(Player& player1, float deltaTime, sf::Vector2f mapSize);
	
	sf::Vector2f target;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f distance;
	float lag = 5.5;
	float maxSpeed;

};

