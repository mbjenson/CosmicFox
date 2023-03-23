#include "Camera.h"


void Camera::update(Player& player1, float deltaTime)
{
	target = player1.getPosition();
	distance.x = player1.getPosition().x - position.x;
	distance.y = player1.getPosition().y - position.y;

	velocity.x = (distance.x * lag) * deltaTime;
	velocity.y = (distance.y * lag) * deltaTime;

	position += velocity;
	setCenter(position);
}

