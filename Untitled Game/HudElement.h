#pragma once
#include "Camera.h"
#include <SFML/Graphics.hpp>

/*
* allows hud elements to be created
* eg. health bar, inventory, etc.
*/
class HudElement : public sf::Drawable, public sf::Transformable
{
public:
	HudElement(sf::Texture& elemTex, sf::Vector2f _screenPos, Camera* _camera);
	sf::Vector2f screenPos;
	sf::Sprite hElemSprite;
	Camera* camera;

private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(hElemSprite, states);
	}
	
};

