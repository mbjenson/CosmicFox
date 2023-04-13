#pragma once
#include "Animation.h"
extern sf::Clock GLOBAL_GAME_CLOCK;

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
	// will be a "pet" and light for player
	// will have movement described below

	// Very much like a terraria lanturn or spirit light thing
	/*
	
void Enemy::basicMovement(sf::Vector2f playPos, sf::Vector2f distVec, float distSize, float dt) {
	attackClock.restart();
	int curTime = attackClock.getElapsedTime().asMilliseconds();
	int redZone = 70;

	if (distSize < detectionRadius) {
		if (curTime < 1000) {
			sf::Vector2f inverseNormalMovement((distVec.x * -1) / distSize, (distVec.y * -1) / distSize);
			sf::Vector2f normalMovement(distVec.x / distSize, distVec.y / distSize);
			if (distSize < redZone) {
				//attackClock.restart();
				// move away from player
				
				float tempRunSpeed = pow((runawaySpeed / distSize), 3) * 10;
				finalVel += sf::Vector2f(inverseNormalMovement.x * dt * tempRunSpeed, inverseNormalMovement.y * dt * tempRunSpeed);
			}
			if (distSize > redZone) {
				float tempMoveSpeed = pow((distSize / moveSpeed), 3) * 10;
				finalVel += sf::Vector2f(normalMovement.x * dt * tempMoveSpeed, normalMovement.y * dt * tempMoveSpeed);
			}
			// apply right and left movements.
			// * sine and cosine are some of the most useful functions in math because they are between -1 and 1 and they change in such unique ways
			// 
			//finalVel.x += sin(GLOBAL_GAME_CLOCK.getElapsedTime().asMilliseconds()) * moveSpeed * dt;
		}
		if (curTime > 1000) {
			// move toward player

		}
	}
	
	

}
	*/
};

