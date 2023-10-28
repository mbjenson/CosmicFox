#pragma once
#include "Enemy.h"

/*
* child class of enemy
* ghost enemy floats around the level and chases the player down and dashes after it when too close.
*/
class GhostEnemy : public Enemy
{
public:
	GhostEnemy(sf::Texture* enemyTex, sf::Vector2u texDim, int rowlength, int rowNumber, float animDuration);

	int initGhost();

	void GhostUpdate(float dt, sf::Vector2f playerPos, TileMap* map, sf::RenderWindow* win);
};

