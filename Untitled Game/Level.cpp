#include "Level.h"

void Level::render(sf::RenderWindow& win) {

	// UPDATING AND DRAWING

	// BACKGROUND LAYER:
	// thirdly, we need to draw the background of the map.

	// BASE LAYER:
	// fourth we check if we need to update base map. the base map is made up of two layers, the "floor", and the "carpet" essentially.
	if (tileMap->checkForUpdate(player->getPosition())) {
		tileMap->updateTexMap();
		tileMap->updatePlayerChunk(player->getPosition());
	}
	sf::Sprite mapSprite(tileMap->mapTex.getTexture());
	win.draw(mapSprite);

	// 3rd LAYER/ Interactable:		
	//						Like the lights, trees, chairs, doors and other things that go above
	//						the floor that can be interacted with.
	//						This layer also need to be drawn with the player and enemies because moving
	//						objects can go in front or behind the interactable tiles.

	sf::Vector2i playerPos(static_cast<int>(player->getPosition().x), static_cast<int>(player->getPosition().y));
	for (int y = tileMap->curDrawArea.top; y < tileMap->curDrawArea.height + tileMap->curDrawArea.top; y++) {
		for (int x = tileMap->curDrawArea.left; x < tileMap->curDrawArea.width + tileMap->curDrawArea.left; x++) {
			if ((playerPos.y - playerPos.y % tileMap->tileSize) / tileMap->tileSize == y && x == (tileMap->curDrawArea.width + tileMap->curDrawArea.left - 1)) {
				win.draw(*player);
			}
			if (tileMap->layer3Types[x + y * tileMap->getMapDimTiles().x] == 0)
				continue;
			else {
				sf::Sprite tempSpr(*tileMap->layer3Texture);
				// sf::Clock animTimer;???
				// use this animTimer to check if tiles should move to the next frame in the animation???
				// create a different class that uses sprites and Animation.h to animate different tiles
				
				// These are specific dimensioins for the interactable layer spriteSheet.
				// Later change this so that these tiles can be animated
				if (tileMap->layer3Types[x + y * tileMap->getMapDimTiles().x] == 1) {
					tempSpr.setTextureRect(tileMap->texDim1);
					tempSpr.setPosition(sf::Vector2f(x * tileMap->tileSize, y * tileMap->tileSize - 4));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * tileMap->getMapDimTiles().x] == 2) {
					tempSpr.setTextureRect(tileMap->texDim2);
					tempSpr.setPosition(sf::Vector2f(x * tileMap->tileSize, y * tileMap->tileSize - tileMap->tileSize - 2));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * tileMap->getMapDimTiles().x] == 3) {
					tempSpr.setTextureRect(tileMap->texDim3);
					tempSpr.setPosition(sf::Vector2f(x * tileMap->tileSize, y * tileMap->tileSize - tileMap->tileSize));
					win.draw(tempSpr);
				}
			}
		}
	}
	// 6th CANOPY LAYER:
		// MAYBE:
		// last, but not least, update the canopy layer
}