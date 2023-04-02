#include "TileMapmk2.h"

TileMapmk2::TileMapmk2(Tile* _tiles, int* types, int* logic) {
	tiles = _tiles;
	tileTypes = types;
	logicGrid = logic;
}

void TileMapmk2::init() {
	mapTex.create(mapDimChunks.x * chunkSize * tileSize, mapDimChunks.y * chunkSize * tileSize);
}

void TileMapmk2::updateAnimations() {
	return;
}

void TileMapmk2::updateDraw(sf::RenderWindow& win) {
	/*
	* sf::IntRect drawArea(0, 0, 3, 3)
	Firstly, check bounds for rect.
	if curChunk.x == 0
		drawArea.left = 0
		drawArea.width -= 1
	if curChunk.y == 0
		drawArea.top = 0
		drawArea.height -= 1
	if curChunk.x == mapDimChunk.x - 1
		drawArea.width -=1;
	if curChunk.y == mapDimChunk.y - 1
		drawArea.height -=1;
	Take curChunk and do following conversion to world float coordinates:
		cornerCurChunk(x, y) => (x * chunkSize * tileSize, y * chunkSize * tileSize);
		then look at tileTypes and set it equal to 


	*/
	
}

void TileMapmk2::updatePlayerChunk(sf::Vector2f playerPos) {
	curChunk = worldToSection(playerPos.x, playerPos.y, chunkSize);
}

sf::Vector2i TileMapmk2::getPlayerChunk() {
	return curChunk;
}


