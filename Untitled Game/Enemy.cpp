#include "Enemy.h"

Enemy::Enemy(sf::Texture* spriteSheet, sf::Vector2f _enemySize) {
	tSprite.setTexture(*spriteSheet);
	enemySize = _enemySize;
	//tSprite.setTextureRect()

};

bool Enemy::init() {
	FLAG_DEAD = false;
	setOrigin(sf::Vector2f(enemySize.x / 2, enemySize.y / 2));
	detectionRadius = 125.f;
	moveSpeed = 50;
	maxHealth = 5;
	curHealth = maxHealth;
	dampingFactor = 0.2;
	hitBox = sf::FloatRect(0, 0, 16, 16);
	// init weapon
	curState = State::nominal;
	beingHit = false;
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

	if (distSize < detectionRadius) {
		sf::Vector2f inverseNormalMovement((distVec.x * -1) / distSize, (distVec.y * -1) / distSize);
		sf::Vector2f normalMovement(distVec.x / distSize, distVec.y / distSize);
		followVel.x -= followVel.x * 0.003;
		followVel.y -= followVel.y * 0.003;
		followVel += sf::Vector2f(dt * normalMovement.x * dampingFactor, dt * normalMovement.y * dampingFactor);
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
		// only loose (damage) health per attack
		
		
		// manage health lose
		// if the 
		//loseHealthTimer.getElapsedTime().asMilliseconds();
		
		// If the player is attack, restart the attack clock
		// keep track of health when the attack happens
		// that way we can change the health value only once when the enemy is attacked.
		
		//int stunTime = stunClock.getElapsedTime().asMilliseconds();
		if (stunClock.getElapsedTime().asMilliseconds() > totalHitTime) {
			//stunClock.restart();
			beingHit = false;
			curState = State::nominal; // this is a crappy way to do this. but for now its fine.
		}
		if (stunClock.getElapsedTime().asMilliseconds() < hitBackTime) {
			// how do big games manage entities. Each one with different information. Each one different sword size, different specs...
			// my temp fix for moving the player away when hes hit is to hard code the radius of the sword and get the distance from outer edge.
			// playerSwordRadiusSize - distSize;
			// then the amount the player moves is proportional to how close the enemy is to the player.
			// the closer the more it moves
			float tempHitSpeed = pow((hitBackSpeed / (distSize)), 2) * 5;
			finalVel = sf::Vector2f(deltaTime * hitVector.x * tempHitSpeed, deltaTime * hitVector.y * tempHitSpeed);
		}
		// stun:
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

void Enemy::getHit(int damage) {
	if (curHealth <= 0)
		FLAG_DEAD = true;
	if (!beingHit)
		curHealth -= damage;
	beingHit = true;
	//damageRecieved = damage;
	stunClock.restart();
	curState = State::attacked;
	
	hitVector = sf::Vector2f(playerDirNormal.x * -1, playerDirNormal.y * -1);
}

void Enemy::revive(sf::Vector2f position) {
	FLAG_DEAD = true;
	setPosition(position);
}

