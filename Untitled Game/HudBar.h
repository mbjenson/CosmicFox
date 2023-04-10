#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"

class HudBar
{
public:
	HudBar(sf::Texture& iconTex, sf::Vector2f _screenPos, Camera* _camera);
	// updates the position of the bar with the corner of the screen
	void render(sf::RenderWindow& win, int quantity);
	
private:
	void update();
	Camera* camera;
	sf::Sprite hSprite;
	sf::Vector2f screenPos;
};

