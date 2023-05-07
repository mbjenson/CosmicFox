#pragma once
#include "Level.h"

class CrashLevel : public Level
{
public:
	CrashLevel(Player* player);

	int init(Player* player);
};

