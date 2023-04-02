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

int TileMapmk2::getTileTypeAt(int x, int y) {
	return tileTypes[x + y * mapDimChunks.x * chunkSize];
}





void TileMapmk2::updateTexMap() {
	// Firstly, check bounds for render rect.
	sf::IntRect drawArea(curChunk.x - 1, curChunk.y - 1, 3, 3);
	if (curChunk.x == 0) {
		drawArea.left = 0;
		drawArea.width -= 1;
	}
	if (curChunk.y == 0) {
		drawArea.top = 0;
		drawArea.height -= 1;
	}
	if (curChunk.x == mapDimChunks.x - 1) {
		drawArea.width -= 1;
	}
	if (curChunk.y == mapDimChunks.y - 1) {
		drawArea.height -= 1;
	}
	//Secondly, go to top left of chunkDrawArea and convert it to world coordinates
	//converting to tile coordinates
	drawArea = sf::IntRect(	drawArea.left * chunkSize, drawArea.top * chunkSize,
							drawArea.width * chunkSize, drawArea.height * chunkSize);

	for (int y = 0; y < drawArea.height; y++){
		for (int x = 0; x < drawArea.width; x++) {
			int curTile = tileTypes[x + y * drawArea.width];
			sf::Sprite tempSpr(*tiles[curTile].tSprite.getTexture());
			tempSpr.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
			mapTex.draw(tempSpr);
		}
	}
	mapTex.display();
}

void TileMapmk2::updatePlayerChunk(sf::Vector2f playerPos) {
	curChunk = worldToSection(playerPos.x, playerPos.y, chunkSize);
}

sf::Vector2i TileMapmk2::getPlayerChunk() {
	return curChunk;
}

sf::RenderTexture* TileMapmk2::getMapTex() {
	return &mapTex;
}
