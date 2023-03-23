#include "TileMap.h"

// create a new class that inherits from this one and create a new version of the contructor and renderer so that it loads things
//	specific to that level

/*
//ABOSULTE PEICE OF BLABBING SHITE CONSTRUCTOR
TileMap::TileMap(	sf::Vector2i _mapSize, int* _tileTypes, int*_logGrid,
					sf::Texture& textureSheet, sf::Vector2u _tileSize)
{
	mapSize = _mapSize; //num tiles in map
	tileTypes = _tileTypes; //array of digits that will represent each tile type
	tileSize = _tileSize; //the pixel size of each tile eg. (32x32)
	tileV.resize(_mapSize.x * _mapSize.y);
	texSheet = textureSheet;

	bool tempBool = false;
	//init the tiles we will use

	grass = Tile(texSheet, false, 1, 0, 0.f);
	grassStone = Tile(texSheet, false, 1, 1, 0.f);
	stoneWall = Tile(texSheet, false, 1, 2, 0.f);
	stone = Tile(texSheet, false, 1, 3, 0.f);
	stairsR = Tile(texSheet, false, 1, 4, 0.f);
	stairsL = Tile(texSheet, false, 1, 5, 0.f);

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			if (_logGrid[x + y * mapSize.x] == 0)
				tempBool = false;
			if (_logGrid[x + y * mapSize.x] == 1)
				tempBool = true;

			//below code is inefficient and bad redo it later 
			if (tileTypes[x + y * mapSize.x] == 0)
			{
				Tile grassC = grass;
				grassC.setPosition(sf::Vector2f(tileSize.x * x, tileSize.y * y));
				grassC.collidable = tempBool;
				tileV.at(x + y * mapSize.x) = grassC;
			}
			if (tileTypes[x + y * mapSize.x] == 1)
			{
				Tile grassStoneC = grassStone;
				grassStoneC.setPosition(sf::Vector2f(tileSize.x * x, tileSize.y * y));
				grassStoneC.collidable = tempBool;
				tileV.at(x + y * mapSize.x) = grassStoneC;
			}
			if (tileTypes[x + y * mapSize.x] == 2)
			{
				Tile stoneWallC = stoneWall;
				stoneWallC.setPosition(sf::Vector2f(tileSize.x * x, tileSize.y * y));
				stoneWallC.collidable = tempBool;
				tileV.at(x + y * mapSize.x) = stoneWallC;
			}
			if (tileTypes[x + y * mapSize.x] == 3)
			{
				Tile stoneC = stone;
				stoneC.setPosition(sf::Vector2f(tileSize.x * x, tileSize.y * y));
				stoneC.collidable = tempBool;
				tileV.at(x + y * mapSize.x) = stoneC;
			}
			if (tileTypes[x + y * mapSize.x] == 4)
			{
				Tile stairsRC = stairsR;
				stairsRC.setPosition(sf::Vector2f(tileSize.x * x, tileSize.y * y));
				stairsRC.collidable = tempBool;
				tileV.at(x + y * mapSize.x) = stairsRC;
			}
			if (tileTypes[x + y * mapSize.x] == 5)
			{
				Tile stairsLC = stairsL;
				stairsLC.setPosition(sf::Vector2f(tileSize.x * x, tileSize.y * y));
				stairsLC.collidable = tempBool;
				tileV.at(x + y * mapSize.x) = stairsLC;
			}

		}
	}
	
}
*/

// PIECE OF GOLD CONSTRUCTOR
TileMap::TileMap(int _numTileTypes, Tile* _tilesArr, sf::Vector2i _mapSize, int* _tileTypes, int* _logGrid, sf::Vector2u _tileSize)
{
	mapSize = _mapSize; //num tiles in map
	tileTypes = _tileTypes; //array of digits that will represent each tile type
	tileSize = _tileSize; //the pixel size of each tile eg. (32x32)
	tileV.resize(_mapSize.x * _mapSize.y);
	tilesArr = _tilesArr;
	numTileTypes = _numTileTypes;
	
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			for (int z = 0; z < _numTileTypes; z++) {
				if (tileTypes[x + y * mapSize.x] == z) {
					Tile curTile = tilesArr[z];
					curTile.setPosition(sf::Vector2f(tileSize.x * x, tileSize.y * y));
					curTile.collidable = _logGrid[x + y * mapSize.x];
					tileV.at(x + y * mapSize.x) = curTile;
				}
			}
		}
	}
}

TileMap::~TileMap() {}

void TileMap::render(sf::Vector2i curTile, sf::RenderWindow& win, sf::Vector2i _rendSize)
{
	//curTile is updated in main and passed in
	sf::IntRect rendArea;
	//calculating the bounds of rendering
	rendArea.left = curTile.x - _rendSize.x;
	rendArea.top = curTile.y - _rendSize.y;
	rendArea.width = (_rendSize.x * 2) + 1;
	rendArea.height = (_rendSize.y * 2) + 1;

	//issue: mixing indexes and numerical values in arithmetic

	if (curTile.x - _rendSize.x < 0) 
	{
		rendArea.left = 0;
		rendArea.width = rendArea.width + (curTile.x - _rendSize.x);
	}
	if (curTile.x + _rendSize.x > mapSize.x - 1) // -1 to mapsize to make it an index
	{
		rendArea.width = rendArea.width - (_rendSize.x - ((mapSize.x - 1) - curTile.x));
	}
	if (curTile.y - _rendSize.y < 0) 
	{
		rendArea.top = 0;
		rendArea.height = rendArea.height + (curTile.y - _rendSize.y);
	}
	if (curTile.y + _rendSize.y > mapSize.y - 1)
	{
		rendArea.height = rendArea.height - (_rendSize.y - ((mapSize.y - 1) - curTile.y));
	}

	for (int y = rendArea.top; y < rendArea.top + rendArea.height; y++)
	{
		for (int x = rendArea.left; x < rendArea.left + rendArea.width; x++)
		{
			int tileIndex = x + y * mapSize.x;
			if (tileIndex >= 0 && tileIndex <= (mapSize.x) * (mapSize.y))
				win.draw(tileV.at(tileIndex));
		}
	}
}

void TileMap::renderAll(sf::RenderWindow& win) {
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			win.draw(getTileAt(x, y));
		}
	}
}

void TileMap::renderRow(sf::Vector2i curTile, int whichRow, sf::Vector2i _rendSize, sf::RenderWindow& win)
{
	//curTile is updated in main and passed in
	// here pass in (1, desired horizontal render width)
	sf::IntRect rendArea;
	//calculating the bounds of rendering
	rendArea.left = curTile.x - _rendSize.x;
	rendArea.top = curTile.y + whichRow;
	rendArea.width = (_rendSize.x * 2) + 1;
	rendArea.height = 1;
	
	if (curTile.x - _rendSize.x < 0)
	{
		rendArea.left = 0;
		rendArea.width = rendArea.width + (curTile.x - _rendSize.x);
	}
	if (curTile.x + _rendSize.x > mapSize.x - 1) // -1 to mapsize to make it an index
	{
		rendArea.width = rendArea.width - (_rendSize.x - ((mapSize.x - 1) - curTile.x));
	}
	if (curTile.y + whichRow < 0)
	{
		return;
	}
	if (curTile.y + whichRow > mapSize.y - 1)
	{
		return;
	}

	int rowNum = curTile.y + whichRow;

	for (int x = rendArea.left; x < rendArea.left + rendArea.width; x++) {
		int tileIndex = x + rowNum * mapSize.x;
		if (tileIndex >= 0 && tileIndex <= (mapSize.x) * (mapSize.y))
			win.draw(getTileAt(x, rowNum));
	}
}

void TileMap::renderOne(sf::RenderWindow& win, int x, int y) {
	win.draw(getTileAt(x, y));
}

Tile TileMap::getTileAt(int x, int y)
{
	return tileV.at(x + y * mapSize.x);
}

Tile TileMap::getTileWithPoints(sf::Vector2f cords) {
	return getTileAt(int(floor(cords.x / tileSize.x)), int(floor(cords.y / tileSize.y)));
}
