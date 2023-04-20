#pragma once

#include "Entity.h"
#include "TileMap.h"
#include <SFML/Graphics.hpp>

extern sf::Clock GLOBAL_GAME_CLOCK;

class Enemy : public Entity
{
public:
	//Enemy(sf::Texture* spriteSheet, sf::Vector2f enemySize);
	Enemy(sf::Texture* spriteSheet, sf::Vector2u texDim, int rowlength, int rowNumber, float animDuration);
	Enemy();
	bool init();

	void revive(sf::Vector2f);

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
	//int damageRecieved;
	bool beingHit;
	
	int damage = 1;
	
	sf::Vector2f moveDir;
	sf::Vector2f finalVel;
	sf::Vector2f followVel;

	// current row in a tileMap;
	int curRow;

	sf::Clock stunClock;
	int hitBackSpeed = 200;
	//int hitBackTime = 90;
	int hitBackTime = 90;
	//int totalHitTime = 200;
	int totalHitTime = 120;

	
	float dampingFactor = 0.2;
	int moveSpeed = 55;
	int runawaySpeed = 70;
	int zoomAttackSpeed = 80;

	int flashTime = 70; // to flash texture red when hurt
	
	State curState;

	int maxHealth;
	int curHealth;

	bool stunned;

	float detectionRadius;

	sf::Vector2f enemySize;

	bool losingHealth;
	int loseHealthCooldown = 50;
	sf::Clock loseHealthTimer;
	
	float distSize;
	sf::Vector2f playerDirNormal; // the normalized vector to the player
	sf::Vector2f hitVector; // the normalized vector captured at the moment the enemy is hit by the player
	//sf::Vector2f prevPlayerPos;
	
	sf::Clock attackClock;
	sf::Vector2f playerDirDashStart;

	bool FLAG_DEAD;
	//sf::Vector2u animDim;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		
		
		
		target.draw(tSprite, states);
	}
	
};

