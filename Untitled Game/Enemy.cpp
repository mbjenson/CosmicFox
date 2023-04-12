#include "Enemy.h"

Enemy::Enemy(sf::Texture* spriteSheet, sf::Vector2f _enemySize) {
	tSprite.setTexture(*spriteSheet);
	enemySize = _enemySize;
	//tSprite.setTextureRect()

};

bool Enemy::init() {
	detectionRadius = 125;
	moveSpeed = 50;
	maxHealth = 5;
	curHealth = maxHealth;
	hitBox = sf::FloatRect(0, 0, 16, 16);
	// init weapon
	curState = State::nominal;
	return true;
}

void Enemy::update(float deltaTime, sf::Vector2f playerPos) {
	
	sf::Vector2f distVec(playerPos.x - getPosition().x, playerPos.y - getPosition().y);
	float distSize = sqrt(pow(distVec.x, 2) + pow(distVec.y, 2));
	playerDirNormal = sf::Vector2f(distVec.x / distSize, distVec.y / distSize);

	switch (curState) {
	case State::nominal:
		moveDir = playerDirNormal;
		if (distSize < detectionRadius) {
			
			move(sf::Vector2f(deltaTime * moveDir.x * moveSpeed, deltaTime * moveDir.y * moveSpeed));
		}
		break;
		// if player in range of attack:
		//		curState = State::attacking
		// 
		// if player 
	//case State::attacking:
		// check if cooldown timer is > cooldown Time
		// attack if can
		// 
	case State::attacked:
		// keep track of health when the attack happens
		// that way we can change the health value only once when the enemy is attacked.
		/*
		if (distSize > 35) {
			curState = State::nominal;
		}
		*/
		if (stunClock.getElapsedTime().asMilliseconds() > totalHitTime) {
			stunClock.restart();
			curState = State::nominal; // this is a crappy way to do this. but for now its fine
		}
		if (stunClock.getElapsedTime().asMilliseconds() < hitBackTime) {
			// how do big games manage entities. Each one with different information. Each one different sword size, different specs...
			// my temp fix for moving the player away when hes hit is to hard code the radius of the sword and get the distance from outer edge.
			// playerSwordRadiusSize - distSize;
			// then the amount the player moves is proportional to how close the enemy is to the player.
			// the closer the more it moves
			float tempHitSpeed = (hitBackSpeed / (distSize)) * 20;
			move(sf::Vector2f(deltaTime * hitVector.x * tempHitSpeed, deltaTime * hitVector.y * tempHitSpeed));
		}
		// stun time:
		if (stunClock.getElapsedTime().asMilliseconds() < totalHitTime) {
			break;
		}
		
	}
	hitBox.left = getPosition().x - hitBox.width / 2;
	hitBox.top = getPosition().y - hitBox.height / 2;
}

void Enemy::getHit() {
	curState = State::attacked;
	
	hitVector = sf::Vector2f(playerDirNormal.x * -1, playerDirNormal.y * -1);
}

