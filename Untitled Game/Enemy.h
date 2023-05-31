#pragma once

#include "Entity.h"
#include "TileMap.h"
#include <SFML/Graphics.hpp>

extern sf::Clock GLOBAL_GAME_CLOCK;

// Base enemy class. Inherits basic functionality from the Entity class
class Enemy : public Entity
{
public:
	Enemy(sf::Texture* spriteSheet, sf::Vector2u texDim, int rowlength, int rowNumber, float animDuration);
	Enemy();
	bool init();

	void revive();

	void setAnimations();
	
	enum class State {
		nominal,
		//attacking,
		attacked,
		dead,
	};

	void update(float deltaTime, sf::Vector2f playerPos, TileMap* map, sf::RenderWindow* win);
	void basicMovement(sf::Vector2f playerPos, sf::Vector2f distanceVec, float distanceSize, float dt);
	void zoomAttack(sf::Vector2f playerPos, sf::Vector2f distanceVec, float distanceSize, float dt); // not used
	void collisionCheckTile(TileMap* map);
	void getHit(int damage);
	void setSpawn(sf::Vector2f);
	//int damageRecieved;
	bool beingHit;
	
	int damage = 1;
	
	sf::Color stdCol;
	sf::Vector2f moveDir;
	sf::Vector2f finalVel;
	sf::Vector2f followVel;
	sf::Vector2f roamVel;

	// current row in a tileMap;
	int curRow;

	sf::Clock stunClock;
	int hitBackSpeed = 200;
	//int hitBackTime = 90;
	int hitBackTime = 90;
	int totalHitTime = 150;
	//int totalHitTime = 120;
	sf::Vector2f spawnpoint;
	
	float dampingFactor = 0.2;
	int moveSpeed = 55;
	int runawaySpeed = 70;
	int zoomAttackSpeed = 80;

	int flashTime = 70; // to flash texture red when hurt
	
	State curState;

	int maxHealth;
	int curHealth;

	bool stunned;
	bool losingHealth;

	float detectionRadius;
	sf::Vector2f enemySize;

	int loseHealthCooldown = 50;
	
	float distSize;
	sf::Vector2f playerDirNormal; // the normalized vector to the player
	sf::Vector2f hitVector; // the normalized vector captured at the moment the enemy is hit by the player
	sf::Vector2f playerDirDashStart;
	
	sf::Clock attackClock;
	sf::Clock loseHealthTimer;
	sf::Clock roamClock;

	float followRadius;

	bool FLAG_CHASING;
	bool FLAG_DEAD;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(tSprite, states);
	}
};

