#include "GhostEnemy.h"

GhostEnemy::GhostEnemy(sf::Texture* enemyTex, sf::Vector2u texDim, int rowLength, int rowNumber, float animDuration) : 
	Enemy(enemyTex, texDim, rowLength, rowNumber, animDuration)
{

}

int GhostEnemy::initGhost() {

	enemySize = sf::Vector2f(24.f, 24.f);
	moveSpeed = 40;
	FLAG_DEAD = false;
	
	setOrigin(sf::Vector2f(enemySize.x / 2, enemySize.y / 2));
	detectionRadius = 100.f;
	
	maxHealth = 5;
	curHealth = maxHealth;
	dampingFactor = 0.2;
	
	hitBox = sf::FloatRect(0, 0, 18, 21);
	distSize = 0.f;
	
	curState = State::nominal;
	beingHit = false;

	
	//idle = true;
	// 
	// This one is default perhaps?
	//prevPlayerPos = sf::Vector2f(200, 200);
	return 0;
}


void Enemy::basicMovement(sf::Vector2f playPos, sf::Vector2f distVec, float distSize, float dt) {
	// define the dashing and facing mechanics
	int dashCooldown = 1000;
	int dashEnd = 1400;
	int curTime = attackClock.getElapsedTime().asMilliseconds();
	
	if (distSize < detectionRadius) {
		sf::Vector2f normalMovement(distVec.x / distSize, distVec.y / distSize);
		if (curTime > dashCooldown && curTime < dashEnd) {
			
			
			followVel.x -= followVel.x * 0.001;
			followVel.y -= followVel.y * 0.001;
			followVel += sf::Vector2f(dt * playerDirDashStart.x * 0.5, dt * playerDirDashStart.y * 0.5);
		}
		if (curTime > dashEnd) {
			playerDirDashStart = sf::Vector2f((playPos.x - getPosition().x)/distSize, (playPos.y - getPosition().y)/distSize);
			attackClock.restart();
		}
		else {
			//sf::Vector2f inverseNormalMovement((distVec.x * -1) / distSize, (distVec.y * -1) / distSize);
			
			followVel.x -= followVel.x * 0.003;
			followVel.y -= followVel.y * 0.003;
			followVel += sf::Vector2f(dt * normalMovement.x * dampingFactor, dt * normalMovement.y * dampingFactor);
		}
	}
	
	
	else {
		// slow enemy down
		followVel.x -= followVel.x * 0.005;
		followVel.y -= followVel.y * 0.005;
	}
	finalVel = followVel;
}


void Enemy::setAnimations() {
	updateRow(0, 1);
	if (distSize > detectionRadius) {
		updateRow(0, 1);
	}
	if (playerDirNormal.x < 0) {
		updateRow(1, 1);
	}
	if (playerDirNormal.x > 0) {
		updateRow(2, 1);
	}
	
	
	// set it so that the ghost is facing towards the player during preperation for attack other wise it is looking away
}

