#pragma once

#include "Entity.h"
#include "Sword.h"
#include <SFML/Graphics.hpp>


/*
The enemy in this game will be able to do several different things.
It can move:
	this means it has animation functions.

It can attack:
	It has a sword.







*/

class Enemy : public Entity
{
public:
	Enemy(sf::Texture* spriteSheet, sf::Vector2f enemySize);
	Enemy();
	bool init();
	
	enum class State {
		nominal,
		attacking,
		attacked,
		dead,
	};

	void update(float deltaTime, sf::Vector2f playerPos);

	void getHit();

	sf::Clock attackClock;
	int attackCooldown = 800;
	sf::Clock stunClock;
	int hitBackSpeed = 275;
	int hitBackTime = 120;
	int totalHitTime = 200;
	
	int moveSpeed = 40;

	int flashTime = 70; // to flash texture red when hurt
	
	State curState;

	int maxHealth;
	int curHealth;

	bool stunned;

	int detectionRadius;

	sf::Vector2f enemySize;

	sf::Vector2f moveDir;
	sf::Vector2f playerDirNormal; // the normalized vector to the player
	sf::Vector2f hitVector; // the normalized vector captured at the moment the enemy is hit by the player
	
	//sf::Vector2u animDim;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		/*
		if (attacking) {
			//target.draw(sword.hBox);

			target.draw(sword);
		}
		*/
		
		target.draw(tSprite, states);
	}
};

