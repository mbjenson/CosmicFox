#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"

/*
* currently an intermediary class between animation and player.
* Created but ended up not being used directly
*/
class Entity : public Animation
{
public:
	Entity(sf::Texture& texSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime);
	Entity();
	~Entity();
	
	sf::FloatRect hitBox;
};