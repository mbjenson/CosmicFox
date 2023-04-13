#pragma once

#include "Entity.h"
#include "TileMap.h"
#include "Sword.h"
#include <SFML/Graphics.hpp>
extern sf::Clock GLOBAL_GAME_CLOCK;

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
		//attacking,
		attacked,
		dead,
	};

	void update(float deltaTime, sf::Vector2f playerPos, TileMap* map, sf::RenderWindow* win);
	void basicMovement(sf::Vector2f playerPos, sf::Vector2f distanceVec, float distanceSize, float dt);
	void zoomAttack(sf::Vector2f playerPos, sf::Vector2f distanceVec, float distanceSize, float dt);

	void getHit();
	
	sf::Vector2f moveDir;
	sf::Vector2f finalVel;
	sf::Vector2f followVel;

	sf::Clock stunClock;
	int hitBackSpeed = 200;
	int hitBackTime = 90;
	int totalHitTime = 200;
	
	float dampingFactor = 0.2;
	int moveSpeed = 55;
	int runawaySpeed = 70;
	int zoomAttackSpeed = 80;

	int flashTime = 70; // to flash texture red when hurt
	
	State curState;

	int maxHealth;
	int curHealth;

	bool stunned;
	

	int detectionRadius;

	sf::Vector2f enemySize;

	bool losingHealth;
	int loseHealthCooldown = 50;
	sf::Clock loseHealthTimer;
	
	sf::Vector2f playerDirNormal; // the normalized vector to the player
	sf::Vector2f hitVector; // the normalized vector captured at the moment the enemy is hit by the player
	//sf::Vector2f prevPlayerPos;
	

	//sf::Vector2u animDim;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(tSprite, states);
	}
};

