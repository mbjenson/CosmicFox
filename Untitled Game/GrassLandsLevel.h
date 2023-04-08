#pragma once
#include "Level.h"
#include "TileMap.h"
class GrassLandsLevel : public Level
{
public:
	GrassLandsLevel();

	void init(TileMap* map, Player* p1);
};

