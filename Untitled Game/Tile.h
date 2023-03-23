#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Tile : public Animation
{
public:
	Tile();

	Tile(sf::Texture& _texture,
		bool isCollidable, int rowLength,
		int rowNumber, float animationTime, sf::Vector2f _position);

	Tile(sf::Texture& _texture,
		bool isCollidable, int rowLength,
		int rowNumber, float animationTime);

	Tile(sf::Texture& _texture, sf::Vector2u _textureDim, bool isCollidable,
		int rowLength, int rowNumber, float animationTime);

	Tile(sf::Texture& _texture, sf::Vector2u _textureDim, int rowNumber);

	~Tile();

	bool collidable = false;
	
private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(tSprite, states);
	}

	

	//sf::FloatRect boundingBox;
	//sf::FloatRect textureBox;

	// tile can have texture bounds and collision bounds

	//bounding lines for collision

};

