#include "TileMapmk2.h"

TileMapmk2::TileMapmk2(int* types, int* logic, sf::Vector2i _mapDimChunks, sf::Texture& _tex) {
	tileTypes = types;
	logicGrid = logic;
	mapDimChunks = _mapDimChunks;
	texSheet = _tex;
}

void TileMapmk2::init() {
	mapTex.create(mapDimChunks.x * chunkSize * tileSize, mapDimChunks.y * chunkSize * tileSize);
}

bool TileMapmk2::check(sf::Vector2f playerPos) {
	sf::Vector2i newChunk(worldToSection(playerPos.x, playerPos.y, chunkSize * tileSize));
	if (curChunk == newChunk) {
		return false;
	}
	else {
		curChunk = newChunk;
		return true;
	}
}

void TileMapmk2::updateAnimations() {
	return;
}

int TileMapmk2::getTileTypeAt(int x, int y) {
	return tileTypes[x + y * mapDimChunks.x * chunkSize];
}

void TileMapmk2::updateTexMap() {
	mapTex.clear();
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
	if (curChunk.x < 0 || curChunk.x > mapDimChunks.x - 1 || curChunk.y < 0 || curChunk.y > mapDimChunks.y - 1)
		return;
	//Secondly, go to top left of chunkDrawArea and convert it to world coordinates
	//converting to tile coordinates
	drawArea = sf::IntRect(	drawArea.left * chunkSize, drawArea.top * chunkSize,
							drawArea.width * chunkSize, drawArea.height * chunkSize);

	for (int y = drawArea.top; y < drawArea.height + drawArea.top; y++){
		for (int x = drawArea.left; x < drawArea.width + drawArea.left; x++) {
			int curTile = tileTypes[x + y * chunkSize * mapDimChunks.x];
			sf::Sprite tempSpr(texSheet);
			tempSpr.setTextureRect(sf::IntRect(0, curTile * tileSize, tileSize, tileSize));
			tempSpr.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
			mapTex.draw(tempSpr);
		}
	}
	mapTex.display();
}

void TileMapmk2::updatePlayerChunk(sf::Vector2f playerPos) {
	curChunk = worldToSection(playerPos.x, playerPos.y, chunkSize * tileSize);
}

sf::Vector2i TileMapmk2::getPlayerChunk() {
	return curChunk;
}

sf::RenderTexture* TileMapmk2::getMapTex() {
	return &mapTex;
}
