#pragma once
#include "Level.h"


class DungeonLevel : public Level
{
public:
	DungeonLevel();

	int init(Player* p1);

	sf::Texture enemyTex;
	
};

/*
How To: Light player shader:
sf::Shader shader;
	if (!shader.loadFromFile("Shaders/test6.frag", sf::Shader::Fragment))
		return -1;
	sf::Vector2i mapPixelDim(newLevel.tileMap->getMapDimTiles().x * newLevel.tileMap->tileSize,
		newLevel.tileMap->getMapDimTiles().y * newLevel.tileMap->tileSize);
	sf::Texture tex;
	tex.create(mapPixelDim.x, mapPixelDim.y);
	sf::Sprite spr(tex);

	shader.setUniform("u_resolution", sf::Vector2f(mapPixelDim.y, mapPixelDim.y));
	shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
	shader.setUniform("radius", 1.f);

	// game loop:

	shader.setUniform("circleCenter", sf::Vector2f(window.mapCoordsToPixel(p1.getPosition())));

			// try and mimic the mouse get position
			window.draw(spr, &shader);

*/

