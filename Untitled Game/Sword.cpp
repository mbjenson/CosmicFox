#include "Sword.h"

Sword::Sword(float _radius, sf::Vector2f _drawOffSet, sf::Texture& texSheet, sf::Vector2u texDim,
	int rowLen, int rowNum, float animTime, int _cooldown, int _swingtime, int _damage) :
	Animation(texSheet, texDim, rowLen, rowNum, animTime) {
	radius = _radius;
	drawOffSet = _drawOffSet;
	cooldown = _cooldown;
	swingTime = _swingtime;
	damage = _damage;
}

Sword::Sword() {}

void Sword::initSword() {
	// the shapes are used for debugging the hitbox
	circleHBox.setRadius(radius);
	circleHBox.setOrigin(sf::Vector2f(radius, radius));
	
	//setOrigin(sf::Vector2f(16, 22));
	setOrigin(drawOffSet);
	notBox.setSize(sf::Vector2f(circleHBox.getRadius() * 4, circleHBox.getRadius() * 2));
	notBox.setOrigin(sf::Vector2f(notBox.getSize().x / 2, -4));
	notBox.setFillColor(sf::Color::Green);
	circleHBox.setFillColor(sf::Color::Red);
}

bool Sword::containsPoint(sf::Vector2f point) {
	if (
		(point.x - circleHBox.getPosition().x) * (point.x - circleHBox.getPosition().x) +
		(point.y - circleHBox.getPosition().y) * (point.y - circleHBox.getPosition().y)
		<= circleHBox.getRadius() * circleHBox.getRadius()) {
		return true;
	}
	return false;
}

bool Sword::checkHit(sf::FloatRect rect) {

	// NOTE: if i did another game, I would use circle hit boxes for the entity hitBoxes

	// if any of the corners or mid edge points are in the circleHBox.
	
	if (containsPoint(sf::Vector2f(rect.left, rect.top)) ||
		containsPoint(sf::Vector2f(rect.left, rect.top + rect.height)) ||
		containsPoint(sf::Vector2f(rect.left + rect.width, rect.top)) ||
		containsPoint(sf::Vector2f(rect.left + rect.width, rect.top + rect.height)) ||
		containsPoint(sf::Vector2f(rect.left + rect.width / 2, rect.top)) ||
		containsPoint(sf::Vector2f(rect.left, rect.top + rect.height / 2)) ||
		containsPoint(sf::Vector2f(rect.left + rect.width, rect.top + rect.height / 2)) ||
		containsPoint(sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height)) ||
		containsPoint(sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2)))
	{
		
		int corners = 0;
		if (notBox.getGlobalBounds().contains(sf::Vector2f(rect.left, rect.top))) {
			corners++;
		}
		if (notBox.getGlobalBounds().contains(sf::Vector2f(rect.left + rect.width, rect.top))) {
			corners++;
		}
		if (notBox.getGlobalBounds().contains(sf::Vector2f(rect.left, rect.top + rect.height))) {
			corners++;
		}
		if (notBox.getGlobalBounds().contains(sf::Vector2f(rect.left + rect.width, rect.top + rect.height))) {
			corners++;
		}
		if (corners >= 4) {
			return false;
		}
		else {
			return true;
		}
	}
}

void Sword::updatePos(sf::Vector2f playerPos) {
	int curTime = swordTimer.getElapsedTime().asMilliseconds();
	if (curTime > swingTime) {
		return;
	}
	circleHBox.setPosition(sf::Vector2f(playerPos.x, playerPos.y));
	notBox.setPosition(sf::Vector2f(playerPos.x, playerPos.y));
	setPosition(sf::Vector2f(playerPos.x, playerPos.y));
}

bool Sword::swing(sf::Vector2f distance) {
	int curTime = swordTimer.getElapsedTime().asMilliseconds();
	if (curTime > cooldown) {
		swordTimer.restart();
	}
	if (curTime >= 0 && curTime <= swingTime) {
		// ** 20 ms margin of delay error
		if (curTime < 10)
			rotate(distance);
		return true;
	}
	if (curTime >= swingTime && curTime <= cooldown)
		return false;

	return false;
}

bool Sword::swing(sf::RenderWindow& win) {
	int curTime = swordTimer.getElapsedTime().asMilliseconds();
	if (curTime > cooldown) {
		swordTimer.restart();
	}
	if (curTime >= 0 && curTime <= swingTime) {
		// ** 20 ms margin of delay error
		if (curTime < 10)
			rotate(win);
		return true;
	}
	if (curTime >= swingTime && curTime <= cooldown)
		return false;
	
	return false;
}

void Sword::rotate(sf::Vector2f distance) {
	float curAngle = (atan2(distance.y, distance.x) * 180.f) / 3.1415926535;
	setRotation(curAngle + 90);
	circleHBox.setRotation(curAngle);
	notBox.setRotation(curAngle + 90);
}

void Sword::rotate(sf::RenderWindow& win) {
	// when first click, calculate the angle and use that for the whole swing 
	sf::Vector2f mouseWorldPos = win.mapPixelToCoords(sf::Mouse::getPosition(win), win.getView());
	sf::Vector2f distance(mouseWorldPos.x - getPosition().x, mouseWorldPos.y - getPosition().y);
	curAngle = (atan2(distance.y, distance.x) * 180) / 3.1415926535;
	setRotation(curAngle + 90);
	circleHBox.setRotation(curAngle);
	notBox.setRotation(curAngle + 90);
	//hBox.setRotation(curAngle + 90);
}

bool Sword::check() {
	if (swordTimer.getElapsedTime().asMilliseconds() > swingTime) {
		return false;
	}
	return true;
}



