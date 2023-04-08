#include "GrassLandsLevel.h"

GrassLandsLevel::GrassLandsLevel() {};

void GrassLandsLevel::init(TileMap* map, Player* p1) {
	tileMap = map;
	player = p1;
	tileMap->texDim1 = sf::IntRect(0, 0, 19, 27);
	//tileMap->texDim2 = sf::IntRect();
	//tileMap->texDim3 = sf::IntRect();
	//tileMap->texDim4 = sf::IntRect();
	//tileMap->texDim5 = sf::IntRect();
	//tileMap->texDim6 = sf::IntRect();
}

