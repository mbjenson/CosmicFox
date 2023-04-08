#include "Level.h"

void Level::render(sf::RenderWindow& win) {
	// Firstly, check bounds for render area.
	sf::IntRect drawArea(tileMap->curChunk.x - 1, tileMap->curChunk.y - 1, 3, 3);
	if (tileMap->curChunk.x == 0) {
		drawArea.left = 0;
		drawArea.width -= 1;
	}
	if (tileMap->curChunk.y == 0) {
		drawArea.top = 0;
		drawArea.height -= 1;
	}
	if (tileMap->curChunk.x == tileMap->mapDimChunks.x - 1) {
		drawArea.width -= 1;
	}
	if (tileMap->curChunk.y == tileMap->mapDimChunks.y - 1) {
		drawArea.height -= 1;
	}
	if (tileMap->curChunk.x < 0 || tileMap->curChunk.x > tileMap->mapDimChunks.x - 1 || tileMap->curChunk.y < 0 || tileMap->curChunk.y > tileMap->mapDimChunks.y - 1)
		return;

	//secondly, go to top left of chunkDrawArea and convert it to world coordinates
	//converting to tile coordinates
	drawArea = sf::IntRect(drawArea.left * tileMap->chunkSize, drawArea.top * tileMap->chunkSize,
		drawArea.width * tileMap->chunkSize, drawArea.height * tileMap->chunkSize);
	// now, in this draw area, we draw the player, the enemies, the tiles, and other things

	// UPDATING AND DRAWING

	// BACKGROUND LAYER:
	// thirdly, we need to draw the background of the map.

	// BASE LAYER:
	// fourth we check if we need to update base map. the base map is made up of two layers, the "floor", and the "carpet" essentially.
	if (tileMap->checkForUpdate(player->getPosition())) {
		tileMap->updateTexMap(drawArea);
		tileMap->updatePlayerChunk(player->getPosition());
	}
	
	sf::Sprite mapSprite(tileMap->mapTex.getTexture());
	win.draw(mapSprite);

	// INTERACTABLE/3rd LAYER:	like the lights, trees, chairs, doors and other things that go above
	//						the floor that can be interacted with.
	//						This layer also need to be drawn with the player and enemies because moving
	//						objects can go in front or behind the interactable tiles.

	sf::Vector2i playerPos(static_cast<int>(player->getPosition().x), static_cast<int>(player->getPosition().y));
	for (int y = 0; y < tileMap->getMapDimTiles().y; y++) {
		for (int x = 0; x < tileMap->getMapDimTiles().x; x++) {
			if ((playerPos.x - playerPos.x % tileMap->tileSize) / tileMap->tileSize == x && (playerPos.y - playerPos.y % tileMap->tileSize) / tileMap->tileSize == y)
				win.draw(*player);
			if (tileMap->layer3Types[x + y * tileMap->getMapDimTiles().x] == 0)
				continue;
			else {
				if (tileMap->layer3Types[x + y * tileMap->getMapDimTiles().x] == 1) {
					sf::Sprite tempSpr(*tileMap->layer3Texture);
					tempSpr.setTextureRect(tileMap->texDim1);
					// the '- 13' and '- 24' exist so that we draw the sprite from the bottom middle of structure up.
					tempSpr.setPosition(sf::Vector2f(x * tileMap->tileSize +13, y * tileMap->tileSize +24));
					//tempSpr.setPosition(sf::Vector2f(x * tileMap->tileSize - 13, y * tileMap->tileSize - 24));

					win.draw(tempSpr);
				}
			}
		}
	}
	// 6th CANOPY LAYER:
		// MAYBE:
		// last, but not least, update the canopy layer
	
}