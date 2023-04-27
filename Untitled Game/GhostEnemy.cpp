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

	stdCol = sf::Color(255, 255, 255, 150);
	//idle = true;
	// 
	// This one is default perhaps?
	//prevPlayerPos = sf::Vector2f(200, 200);
	return 0;
}




void Enemy::basicMovement(sf::Vector2f playPos, sf::Vector2f distVec, float distSize, float dt) {
	// define the dashing and facing mechanics
	
	// start by pursuing the player at a slow speed for 500ms
	// pause for 100 ms
	// gather player position and dash at player for 200ms
	// pause for 100ms
	// > restart

	int pursuePlayerTime = 2200;
	int prepDashTime = 2600;
	int dashTime = 3000;
	int pause = 3200;

	int dashSpeed = 180;
	
	int curTime = attackClock.getElapsedTime().asMilliseconds();
	
	if (distSize < detectionRadius) {
		sf::Vector2f normalMovement(distVec.x / distSize, distVec.y / distSize);
		if (curTime > pause) {
			//sf::Vector2f inverseNormalMovement((distVec.x * -1) / distSize, (distVec.y * -1) / distSize);
			attackClock.restart();
			
		}
		else if (curTime > dashTime) {

			// PAUSE
			followVel = sf::Vector2f(0, 0);
			//followVel.x -= followVel.x * 0.01;
			//followVel.y -= followVel.y * 0.01;
			
		}
		else if (curTime > prepDashTime) {
			// DASH

			followVel = sf::Vector2f(dt * playerDirDashStart.x * dashSpeed, dt * playerDirDashStart.y * dashSpeed);

			//followVel.x -= followVel.x * 0.01;
			//followVel.y -= followVel.y * 0.01;
			//attackClock.restart();
		}
		else if (curTime > prepDashTime - 20) {
			playerDirDashStart = sf::Vector2f((playPos.x - getPosition().x) / distSize, (playPos.y - getPosition().y) / distSize);
		}
		else if (curTime > pursuePlayerTime) {
			// PAUSE
			//followVel = sf::Vector2f(0, 0);
			followVel.x -= followVel.x * 0.04;
			followVel.y -= followVel.y * 0.04;
			//followVel += sf::Vector2f(dt * playerDirDashStart.x, dt * playerDirDashStart.y);
		}
		else if (curTime < pursuePlayerTime) {
			// PURSUE
			followVel.x -= followVel.x * 0.003;
			followVel.y -= followVel.y * 0.003;
			followVel += sf::Vector2f(dt * normalMovement.x * dampingFactor, dt * normalMovement.y * dampingFactor);
		}
	}
	
	else {
		attackClock.restart();
		// slow enemy down
		followVel.x -= followVel.x * 0.005;
		followVel.y -= followVel.y * 0.005;
	}
	
	finalVel = followVel;
	finalVel.y += sin(GLOBAL_GAME_CLOCK.getElapsedTime().asSeconds() * 2) * dt * 8;

}


void Enemy::setAnimations() {
	updateRow(0, 1);
	/*
	if (distSize > detectionRadius) {
		updateRow(0, 1);
	}
	if (playerDirNormal.x < 0) {
		updateRow(1, 1);
	}
	if (playerDirNormal.x > 0) {
		updateRow(2, 1);
	}
	*/
	
	
	// set it so that the ghost is facing towards the player during preperation for attack other wise it is looking away
}

