#include "Spirit.h"

Spirit::Spirit(sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime)
	: Animation(texSheet, texDim, rowLen, rowNum, animTime) 
{
	
}

void Spirit::init() {
	finalVel = sf::Vector2f(0.f, 0.f);
	dampFact = 0.5f;
	friction = 0.05f;
	
	lastPlayerPosX = 0.f;
	
}

void Spirit::update(sf::Vector2f playerPos, float dt) {

	sf::Vector2f distance;
	if (lastPlayerPosX - playerPos.x > 0) {
		// facing left
		distance = sf::Vector2f((playerPos.x + 8.f) - getPosition().x, (playerPos.y - 15.f) - getPosition().y);
		lastDir = 0;
	}
	if (lastPlayerPosX - playerPos.x < 0) {
		// facing right
		distance = sf::Vector2f((playerPos.x - 15.f) - getPosition().x, (playerPos.y - 15.f) - getPosition().y);
		lastDir = 1;
	}
	else { // stationary
		if (lastDir == 1) 
			distance = sf::Vector2f((playerPos.x - 15.f) - getPosition().x, (playerPos.y - 15.f) - getPosition().y);
		else
			distance = sf::Vector2f((playerPos.x + 7.f) - getPosition().x, (playerPos.y - 15.f) - getPosition().y);
	}
	//float distSize = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	//sf::Vector2f normalMove(distance.x / distSize, distance.y / distSize);
	finalVel.x += dt * (distance.x * dampFact);
	finalVel.y += dt * (distance.y * dampFact);
	finalVel.x -= finalVel.x * friction;
	finalVel.y -= finalVel.y * friction;

	finalVel.y += sin(GLOBAL_GAME_CLOCK.getElapsedTime().asSeconds() * 4) * dt;
	move(finalVel);

	updateAnim();
	lastPlayerPosX = playerPos.x;
	
	//light.setPosition(sf::Vector2f((light.getPosition().x + finalVel.x) - 12, light.getPosition().y + finalVel.y));
	//light.setPosition(sf::Vector2f(getPosition().x - 12, getPosition().y - inverseBobbing));
}