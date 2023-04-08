#include "Entity.h"

Entity::Entity() {};
Entity::~Entity() {};
Entity::Entity(sf::Texture& texSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime) : 
	Animation(texSheet, textureDim, rowLength, rowNumber, animationTime)
{
	
}

