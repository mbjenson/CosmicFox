#include "Camera.h"


void Camera::update(Player& player1, float deltaTime, sf::Vector2f mapSize)
{
	if (player1.FLAG_FALL) {
		return;
	}
	target = player1.getPosition();
	distance.x = player1.getPosition().x - position.x;
	distance.y = player1.getPosition().y - position.y;

	velocity.x = (distance.x * lag) * deltaTime;
	velocity.y = (distance.y * lag) * deltaTime;

	position += velocity;

	

	int outOfBounds = 0;
	sf::Vector2f tempCenter(position);
	if (position.x - getSize().x / 2 < 0) {
		tempCenter.x = getSize().x / 2;
		outOfBounds++;
	}
	if (position.y - getSize().y / 2 < 0) {
		tempCenter.y = getSize().y / 2;
		outOfBounds++;
	}
	if (position.x + getSize().x / 2 > mapSize.x) {
		tempCenter.x = mapSize.x - getSize().x / 2;
		outOfBounds++;
	}
	if (position.y + getSize().y / 2 > mapSize.y) {
		tempCenter.y = mapSize.y - getSize().y / 2;
		outOfBounds++;
	}
	if (outOfBounds > 0)
		setCenter(tempCenter);
	else
		setCenter(position);
}

