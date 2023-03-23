#include "Entity.h"


Entity::Entity() {};

Entity::~Entity() {};

Entity::Entity(sf::Texture& texSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime) : 
	Animation(texSheet, textureDim, rowLength, rowNumber, animationTime)
{
	
}




/*

Entity::Entity() {}

Entity::Entity(sf::Texture& texture)
{
	eSprite.setTexture(texture);
}

*/

// rudementary implementation of animating this entity
// it assums all animations have the same number of frames
/*
Entity::Entity(sf::Texture& texture, int _rowNum, int _rowLen, sf::Vector2u _individualSize)
{
	//dont have to do all this, just pass in a pointer to an animation struct or something
	eSprite.setTexture(texture);
	rowNum = _rowNum;
	rowLen = _rowLen;
	individualSize = _individualSize;
	
	//start on the left side of the sheet at the given row
	eSprite.setTextureRect(sf::IntRect(
		0, _rowNum * _individualSize.y,
		_individualSize.x, _individualSize.y));
	textureRect = eSprite.getTextureRect();
}

void Entity::changeRow(int newRow)
{
	rowNum = newRow;
}

void Entity::updateAnimation()
{
	if (textureRect.left >= rowLen * individualSize.x)
	{
		textureRect.left = 0;
		// go to beginning
	}
	else
	{
		textureRect.left += individualSize.x;
		// move to next one
	}
}
*/
