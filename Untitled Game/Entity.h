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

	sf::FloatRect hitBox;

};


/*
class Entity : public sf::Drawable, public sf::Transformable
{
public:

	Entity();
	Entity(sf::Texture& texture);
	sf::Sprite eSprite;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(eSprite, states);
		
	}
	
};
*/

