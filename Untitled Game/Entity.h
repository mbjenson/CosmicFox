#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"

//currently an intermediary class between animation and player, this is here incase I need to increase abstraction
class Entity : public Animation
{
public:

	Entity(sf::Texture& texSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime);
	Entity();
	~Entity();
	
	// a function that takes in the hitBox of another entity and sees if the convex shape of sword has hit it.
	// can only check if a floatrect has intersected with the convex sword hBox so we must check it in the player/ enemy classes
	
	sf::FloatRect hitBox;
	//int health;	

};