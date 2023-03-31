#include "Sword.h"

Sword::Sword(Player& _player, sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime) :
	Animation(texSheet, texDim, rowLen, rowNum, animTime)
{
	player = &_player;
}

Sword::Sword() {}

void Sword::swing(float angle) {
	tSprite.setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y));
	// play around with loading things in and out.
	// for eg, load in the hitbox for sword, then be rid of it after it is done.
	
	// firstly, innit a new hitbox for a given swing.
	
}

void Sword::initSword() {
	
	hBox.setPointCount(7);
	hBox.setPoint(0, sf::Vector2f(3, 16));
	hBox.setPoint(1, sf::Vector2f(4, 10));
	hBox.setPoint(2, sf::Vector2f(8, 4));
	hBox.setPoint(3, sf::Vector2f(16, 1));
	hBox.setPoint(4, sf::Vector2f(24, 4));
	hBox.setPoint(5, sf::Vector2f(28, 10));
	hBox.setPoint(6, sf::Vector2f(29, 16));

	hBox.setFillColor(sf::Color::Red);
	hBox.setOrigin(sf::Vector2f(8, 10));
	tSprite.setOrigin(sf::Vector2f(8, 8));
}

void Sword::update() {
	hBox.setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y));
	tSprite.setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y));

}





