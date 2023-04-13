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
	// This one is default perhaps?
	//prevPlayerPos = sf::Vector2f(200, 200);
	return true;
}

void Enemy::zoomAttack(sf::Vector2f playPos, sf::Vector2f distVec, float distSize, float dt) {
	
}
// more interesting movement for enemy.
// this time the enemy will try and stay a certain distance away from the player and go in for an attack if
// it deems it necessary

void Enemy::basicMovement(sf::Vector2f playPos, sf::Vector2f distVec, float distSize, float dt) {
	
	
	int redZone = 40;

	if (distSize < detectionRadius) {
		
		sf::Vector2f inverseNormalMovement((distVec.x * -1) / distSize, (distVec.y * -1) / distSize);
		sf::Vector2f normalMovement(distVec.x / distSize, distVec.y / distSize);
		dampingFactor = 0.35;
		//sf::Vector2f playerVel(prevPlayerPos.x - playPos.x, prevPlayerPos.y - playPos.y);
		
		
		
		followVel.x -= followVel.x * 0.005;
		followVel.y -= followVel.y * 0.005;
		followVel += sf::Vector2f(dt * normalMovement.x * dampingFactor, dt * normalMovement.y * dampingFactor);
			// apply right and left movements.
			// * sine and cosine are some of the most useful functions in math because they are between -1 and 1 and they change in such unique ways
			// 
			//finalVel.x += sin(GLOBAL_GAME_CLOCK.getElapsedTime().asMilliseconds()) * moveSpeed * dt;
	}
	else {
		followVel.x -= followVel.x * 0.005;
		followVel.y -= followVel.y * 0.005;
	}
	finalVel = followVel;

		// perform random idle movements;
		//int choice = rand();
		// move two sqares, change facing, do other random things
}

void Enemy::update(float deltaTime, sf::Vector2f playerPos, TileMap* map, sf::RenderWindow* win) {
	
	sf::Vector2f distVec(playerPos.x - getPosition().x, playerPos.y - getPosition().y);
	float distSize = sqrt(pow(distVec.x, 2) + pow(distVec.y, 2));
	playerDirNormal = sf::Vector2f(distVec.x / distSize, distVec.y / distSize);

	switch (curState) {
	case State::nominal:
	{
		basicMovement(playerPos, distVec, distSize, deltaTime);
		break;
		//move(finalVel);
	}
	case State::attacked:
		// manage health lose
		// if the 
		//loseHealthTimer.getElapsedTime().asMilliseconds();
		
		// If the player is attack, restart the attack clock
		// keep track of health when the attack happens
		// that way we can change the health value only once when the enemy is attacked.
		/*
		if (distSize > 35) {
			curState = State::nominal;
		}
		*/
		followVel = sf::Vector2f(0, 0);
		if (stunClock.getElapsedTime().asMilliseconds() > totalHitTime) {
			stunClock.restart();
			curState = State::nominal; // this is a crappy way to do this. but for now its fine.
		}
		if (stunClock.getElapsedTime().asMilliseconds() < hitBackTime) {
			// how do big games manage entities. Each one with different information. Each one different sword size, different specs...
			// my temp fix for moving the player away when hes hit is to hard code the radius of the sword and get the distance from outer edge.
			// playerSwordRadiusSize - distSize;
			// then the amount the player moves is proportional to how close the enemy is to the player.
			// the closer the more it moves
			// NOTE: added pow since last build******
			float tempHitSpeed = pow((hitBackSpeed / (distSize)), 2) * 5;
			finalVel = sf::Vector2f(deltaTime * hitVector.x * tempHitSpeed, deltaTime * hitVector.y * tempHitSpeed);
		}
		// stun time:
		if (stunClock.getElapsedTime().asMilliseconds() < totalHitTime) {
			break;
		}
	}
	// update hitBox Pos:
	hitBox.left = getPosition().x - hitBox.width / 2;
	hitBox.top = getPosition().y - hitBox.height / 2;
	// update Sword:
	
	// update Animations:

	// collision checks
	
	// final vel
	move(finalVel);
	//prevPlayerPos = playerPos;
}

void Enemy::getHit() {
	curState = State::attacked;
	hitVector = sf::Vector2f(playerDirNormal.x * -1, playerDirNormal.y * -1);
}

