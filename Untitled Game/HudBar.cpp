#include "HudBar.h"

HudBar::HudBar(sf::Texture& iconTex, sf::Vector2f _screenPos, int initQuan, sf::Vector2u _texSize) {
	hSprite.setTexture(iconTex);
	screenPos = _screenPos;
	initQuanitity = initQuan;
	texSize = _texSize;
	
}

void HudBar::update(sf::Vector2f cCenter, sf::Vector2f cSize) {
	hSprite.setPosition(sf::Vector2f(cCenter.x - (cSize.x / 2) + screenPos.x,
		cCenter.y - (cSize.y / 2) + screenPos.y));
}

void HudBar::render(sf::RenderWindow& win, int quantity, sf::Vector2f topLeft) {
	
	hSprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
	hSprite.setPosition(sf::Vector2f(topLeft.x + screenPos.x, topLeft.y + screenPos.y));

	//hSprite.setTextureRect(sf::IntRect(0, 0, hSprite.getGlobalBounds().width / 2, hSprite.getGlobalBounds().height));
	for (int i = 0; i < initQuanitity; i++) {
		if (i < quantity) {
			hSprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
		}
		else {
			hSprite.setTextureRect(sf::IntRect(texSize.x, 0, texSize.x, texSize.y));
		}
		//hSprite.setTextureRect()
		win.draw(hSprite);
		hSprite.setPosition(hSprite.getPosition().x + hSprite.getGlobalBounds().width + 2, hSprite.getPosition().y);
		
			//hSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
		
		
			//hSprite.setTextureRect(sf::IntRect(textureSize.x, 0, textureSize.x, textureSize.y));
		

		
		//win.draw(hSprite);
	}
	
}