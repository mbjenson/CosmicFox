#include "HudBar.h"

HudBar::HudBar(sf::Texture& iconTex, sf::Vector2f _screenPos, Camera* _camera) {
	hSprite.setTexture(iconTex);
	camera = _camera;
	screenPos = _screenPos;
}

void HudBar::update() {
	hSprite.setPosition(sf::Vector2f(camera->getCenter().x - (camera->getSize().x / 2) + screenPos.x,
		camera->getCenter().y - (camera->getSize().y / 2) + screenPos.y));
}

void HudBar::render(sf::RenderWindow& win, int quantity) {
	update();
	for (int i = 0; i < quantity; i++) {
		win.draw(hSprite);
		hSprite.setPosition(sf::Vector2f(hSprite.getPosition().x + hSprite.getGlobalBounds().width, hSprite.getPosition().y));
	}
	
}