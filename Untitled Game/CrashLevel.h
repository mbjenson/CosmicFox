#pragma once
#include "Level.h"

/*
* Crash level is a Level in the game
*/
class CrashLevel : public Level
{
public:
	CrashLevel(Player* player);

	int init(Player* player);
};

