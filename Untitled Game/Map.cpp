#include "Map.h"

Map::Map()
{
	gridLen = 8;
	setUpInitialState();

}

void Map::setUpInitialState()
{
	exitPos = sf::Vector2i(1, 0);
	playerPos = sf::Vector2i(gridLen - 1, gridLen - 1);
	setUpEnemyPositions();
}

void Map::setUpEnemyPositions()
{
	enemyPositions.clear();
	enemyPositions.push_back(sf::Vector2i(0, 2));
	enemyPositions.push_back(sf::Vector2i(6, 0));
	enemyPositions.push_back(sf::Vector2i(2, 7));
}

void Map::setUpTiles()
{
	tiles.clear();
	std::vector<GameTile*> firstRow;
	firstRow.push_back(new GameTile("textures/wall.png", 0, 0, false, false));
	firstRow.push_back(new GameTile("textures/wall.png", 50, 0, false, false));
	firstRow.push_back(new GameTile("textures/wall.png", 100, 0, false, false));
	firstRow.push_back(new GameTile("textures/wall.png", 150, 0, false, false));
	firstRow.push_back(new GameTile("textures/wall.png", 200, 0, false, false));
	firstRow.push_back(new GameTile("textures/wall.png", 250, 0, false, false));
	firstRow.push_back(new GameTile("textures/wall.png", 300, 0, false, false));
	firstRow.push_back(new GameTile("textures/wall.png", 350, 0, false, false));
	tiles.push_back(firstRow);

	
	std::vector<GameTile*> secondRow;
	secondRow.push_back(new GameTile("textures/grass.png", 0, 50, false, false));
	secondRow.push_back(new GameTile("textures/grass.png", 50, 50, false, false));
	secondRow.push_back(new GameTile("textures/grass.png", 100, 50, false, false));
	secondRow.push_back(new GameTile("textures/grass.png", 150, 50, false, false));
	secondRow.push_back(new GameTile("textures/grass.png", 200, 50, false, false));
	secondRow.push_back(new GameTile("textures/grass.png", 250, 50, false, false));
	secondRow.push_back(new GameTile("textures/grass.png", 300, 50, false, false));
	secondRow.push_back(new GameTile("textures/grass.png", 350, 50, false, false));
	tiles.push_back(secondRow);

}