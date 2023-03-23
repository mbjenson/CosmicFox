#pragma once
#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef MAP_H
#define MAP_H

class Map
{
public:
	std::vector< std::vector<GameTile*> > tiles;
	int gridLen;
	Map();

private:
	sf::Vector2i exitPos;
	sf::Vector2i playerPos;
	std::vector<sf::Vector2i> enemyPositions;
	void setUpInitialState();
	void setUpEnemyPositions();
	void setUpTiles();
};

#endif