#include "HudBar.h"

HudBar::HudBar(sf::Texture& iconTex, sf::Vector2f _screenPos) {
	hSprite.setTexture(iconTex);
	screenPos = _screenPos;
}

void HudBar::update(sf::Vector2f cCenter, sf::Vector2f cSize) {
	hSprite.setPosition(sf::Vector2f(cCenter.x - (cSize.x / 2) + screenPos.x,
		cCenter.y - (cSize.y / 2) + screenPos.y));
}

void HudBar::render(sf::RenderWindow& win, int quantity, sf::Vector2f cCenter, sf::Vector2f cSize) {
	update(cCenter, cSize);
	for (int i = 0; i < quantity; i++) {
		win.draw(hSprite);
		hSprite.setPosition(sf::Vector2f(hSprite.getPosition().x + hSprite.getGlobalBounds().width + 2, hSprite.getPosition().y));
	}
}