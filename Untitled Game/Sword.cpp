#include "Sword.h"

Sword::Sword(sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime) :
	Animation(texSheet, texDim, rowLen, rowNum, animTime) {}

Sword::Sword() {}

void Sword::initSword() {
	
	hBox.setPointCount(7);
	hBox.setPoint(0, sf::Vector2f(3, 16));
	hBox.setPoint(1, sf::Vector2f(4, 10));
	hBox.setPoint(2, sf::Vector2f(8, 4));
	hBox.setPoint(3, sf::Vector2f(16, 1));
	hBox.setPoint(4, sf::Vector2f(24, 4));
	hBox.setPoint(5, sf::Vector2f(28, 10));
	hBox.setPoint(6, sf::Vector2f(29, 16));
	hBox.setOrigin(sf::Vector2f(16, 24));
	setOrigin(sf::Vector2f(16, 22));
}

void Sword::updatePos(sf::Vector2f playerPos) {
	int curTime = swordTimer.getElapsedTime().asMilliseconds();
	if (curTime > swingTime) {
		return;
	}
	hBox.setPosition(sf::Vector2f(playerPos.x, playerPos.y));
	setPosition(sf::Vector2f(playerPos.x, playerPos.y));
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

void Sword::rotate(sf::RenderWindow& win) {
	// when first click, calculate the angle and use that for the whole swing 
	sf::Vector2f mouseWorldPos = win.mapPixelToCoords(sf::Mouse::getPosition(win), win.getView());
	sf::Vector2f distance(mouseWorldPos.x - getPosition().x, mouseWorldPos.y - getPosition().y);
	curAngle = (atan2(distance.y, distance.x) * 180.f) / 3.1415926535;
	setRotation(curAngle + 90);
	hBox.setRotation(curAngle + 90);
}

bool Sword::check() {
	if (swordTimer.getElapsedTime().asMilliseconds() > swingTime) {
		return false;
	}
	return true;
}





