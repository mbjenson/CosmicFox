#include "Enemy.h"

Enemy::Enemy(sf::Texture* spriteSheet) {
	//tSprite.setTexture(*spriteSheet);
	//tSprite.setTextureRect()
};

Enemy::Enemy() {
	rect.setSize(sf::Vector2f(16, 16));
	rect.setFillColor(sf::Color::Cyan);

}
