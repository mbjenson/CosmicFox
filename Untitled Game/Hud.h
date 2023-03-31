#pragma once
#include "HudElement.h"

// just includes a bunch of hud elements in it that can be drawn
class Hud {
public:
	Hud(std::vector<HudElement>* _elemVec);
	void render(sf::RenderWindow& win);
private:
	std::vector<HudElement> elemVec;
};

