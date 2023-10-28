#pragma once
#include "Animation.h"
extern sf::Clock GLOBAL_GAME_CLOCK;

/*
* Spirit class
* the spirit is the companion flame friend of the fox that follows him around the level
*/
class Spirit : public Animation
{
public:
	Spirit(sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime);

	void init();
	void update(sf::Vector2f playerPos, float dt);
	float dampFact;
	float friction;
	float lastPlayerPosX;
	sf::Vector2f targetPos;
	sf::Vector2f finalVel;
	
	char lastDir;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		
		
		//target.draw(light);
		target.draw(tSprite, states);
	}
};

