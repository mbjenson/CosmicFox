#include "GhostEnemy.h"

GhostEnemy::GhostEnemy(sf::Texture* enemyTex, sf::Vector2u texDim, int rowLength, int rowNumber, float animDuration) : 
	Enemy(enemyTex, texDim, rowLength, rowNumber, animDuration)
{}

int GhostEnemy::initGhost() {

	enemySize = sf::Vector2f(24.f, 24.f);
	moveSpeed = 40;
	FLAG_DEAD = false;
	
	setOrigin(sf::Vector2f(enemySize.x / 2, enemySize.y / 2));
	detectionRadius = 70.f; // won't be needing this
	followRadius = 100.f; // or this
	
	FLAG_CHASING = false;
	
	maxHealth = 5;
	curHealth = maxHealth;
	dampingFactor = 0.5; 
	
	//hitBox = sf::FloatRect(0, 0, 18, 21);
	hitBox = sf::FloatRect(0, 0, 16, 16); // new, more fair hitbox
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
	
	// start by pursuing the player at a slow speed for 500ms
	// pause for 100 ms
	// gather player position and dash at player for 200ms
	// pause for 100ms
	// > restart

	//int pursuePlayerTime = 5000;
	int pursuePlayerTime = 1000 * curHealth;
	// old 2220
	int prepDashTime = pursuePlayerTime + 400;
	//int prepDashTime = 5400;
	// old 2600
	int dashTime = pursuePlayerTime + 800;
	//int dashTime = 5800;
	// old 3000
	int pause = pursuePlayerTime + 1000;
	//int pause = 6000;
	// old 3200

	int dashSpeed = 115;
	// old : 180
	
	int curTime = attackClock.getElapsedTime().asMilliseconds();
	//if (distSize < detectionRadius)
	FLAG_CHASING = true;
	
	//if (FLAG_CHASING && distSize < followRadius) {
	sf::Vector2f movementVector(distVec.x / distSize, distVec.y / distSize);
	if (distSize < 100.f) {
		
		if (curTime > pause) {
			//sf::Vector2f inverseNormalMovement((distVec.x * -1) / distSize, (distVec.y * -1) / distSize);
			attackClock.restart();
		}
		else if (curTime > dashTime) {
			// PAUSE
			//followVel = sf::Vector2f(0, 0);
			followVel.x -= followVel.x * 0.06;
			followVel.y -= followVel.y * 0.06;
		}
		else if (curTime > prepDashTime) {
			// DASH
			followVel = sf::Vector2f(dt * playerDirDashStart.x * dashSpeed, dt * playerDirDashStart.y * dashSpeed);
		}
		else if (curTime > prepDashTime - 150 && curTime < prepDashTime - 130) {
			playerDirDashStart = sf::Vector2f((playPos.x - getPosition().x) / distSize, (playPos.y - getPosition().y) / distSize);
		}
		else if (curTime > pursuePlayerTime) {
			// PAUSE
			//followVel = sf::Vector2f(0, 0);
			followVel.x -= followVel.x * 0.06;
			followVel.y -= followVel.y * 0.06;
			//followVel += sf::Vector2f(dt * playerDirDashStart.x, dt * playerDirDashStart.y);
		}
		else if (curTime < pursuePlayerTime) {
			// PURSUE
			followVel.x -= followVel.x * 0.009; // friction..
			followVel.y -= followVel.y * 0.009; // friction..
			followVel += sf::Vector2f(dt * movementVector.x * dampingFactor, dt * movementVector.y * dampingFactor);
		}
	}
	else {
		followVel.x -= followVel.x * 0.009; // friction..
		followVel.y -= followVel.y * 0.009; // friction..
		followVel += sf::Vector2f(dt * movementVector.x * dampingFactor, dt * movementVector.y * dampingFactor);
	}
	
	finalVel = followVel + roamVel;

	// hovering movement
	finalVel.y += sin(GLOBAL_GAME_CLOCK.getElapsedTime().asSeconds() * 2) * dt * 8;

}

// didn't end up animating the ghost...
void Enemy::setAnimations() {
	updateRow(0, 1);
	
}

