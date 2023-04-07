#include "TileMapmk2.h"

TileMapmk2::TileMapmk2(int* types1, int* types2, int* logic, sf::Vector2i _mapDimChunks, sf::Texture* layer1, sf::Texture* layer2) {
	layer1Types = types1;
	layer2Types = types2;
	logicGrid = logic;
	mapDimChunks = _mapDimChunks;
	layer1Texture = layer1;
	layer2Texture = layer2;
	//layer3Texture = layer3;
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
// WIP
void TileMapmk2::updateAnimations() {
	return;
}

int TileMapmk2::getTileTypeAt(int x, int y) {
	return layer1Types[x + y * mapDimChunks.x * chunkSize];
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
			int curTile = layer1Types[x + y * chunkSize * mapDimChunks.x];
			int curTile2 = layer2Types[x + y * chunkSize * mapDimChunks.x];
			sf::Sprite tempSpr1(*layer1Texture);
			tempSpr1.setTextureRect(sf::IntRect(0, curTile * tileSize, tileSize, tileSize));
			tempSpr1.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
			sf::Sprite tempSpr2(*layer2Texture);
			tempSpr2.setTextureRect(sf::IntRect(0, curTile2 * tileSize, tileSize, tileSize));
			tempSpr2.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
			mapTex.draw(tempSpr1);
			mapTex.draw(tempSpr2);
		}
	}
	mapTex.display();
}

int TileMapmk2::getTileLogic(sf::Vector2f playerPos) {
	// player pos / tile size = current tile
	// then I can use that to extract the value at that index in the logic grid
	sf::Vector2i currentTile(static_cast<int>(playerPos.x) / tileSize, static_cast<int>(playerPos.y) / tileSize);
	return (logicGrid[currentTile.x + currentTile.y * mapDimChunks.x * chunkSize]);
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

sf::Vector2i TileMapmk2::getMapDimTiles() {
	return mapDimChunks * chunkSize;
}

int TileMapmk2::getTileSize() {
	return tileSize;
}

sf::Vector2i TileMapmk2::getTileWithCoords(sf::Vector2f coords) {
	return (sf::Vector2i(static_cast<int>(coords.x) / tileSize, static_cast<int>(coords.y) / tileSize));
}

sf::Vector2f TileMapmk2::getTilePos(sf::Vector2f coords) {
	return (sf::Vector2f(coords.x - fmod(coords.x, tileSize), coords.y - fmod(coords.y, tileSize)));
}