#pragma once
#include "Level.h"

class GrassLandsLevel : public Level
{
public:
	GrassLandsLevel();

	int init(TileMap* map, Player* p1);

	int init(Player* p1);
};

