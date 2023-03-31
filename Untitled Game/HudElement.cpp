#include "HudElement.h"

HudElement::HudElement(sf::Texture& elemTex, sf::Vector2f _screenPos, Camera* camera) {
	hElemSprite.setTexture(elemTex);
	screenPos = _screenPos;
	camera = camera;
}





