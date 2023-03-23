#pragma once
#include "SFML/Graphics.hpp"

class Projectile : public sf::Drawable, public sf::Transformable
{
public:
	Projectile(sf::Texture& texture);
private:
	sf::Sprite pSprite;

};