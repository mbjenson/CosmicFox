#pragma once
#include "Level.h"
#include "GhostEnemy.h"


class GrassLandsLevel : public Level
{
public:
	GrassLandsLevel();

	int init(TileMap* map, Player* p1);

	int init(Player* p1);

	sf::Texture ghostTex;
};

