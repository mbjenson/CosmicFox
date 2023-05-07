#pragma once
#include "Level.h"

class IntroLevel : public Level
{
public:
	IntroLevel(Player* player);
	
	int init(Player* p1);
};

