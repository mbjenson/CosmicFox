#include "Hud.h"

Hud::Hud(std::vector<HudElement>* _elemVec) {
	elemVec = *_elemVec;
}

void Hud::render(sf::RenderWindow& win) {
	for (int i = 0; i < elemVec.size(); i++) {
		win.draw(elemVec.at(i));
	}
	
}