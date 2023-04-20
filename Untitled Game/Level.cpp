#include "Level.h"

void Level::render(sf::RenderWindow& win) {

	// UPDATING AND DRAWING:

	// BACKGROUND LAYER:
	
	// we need to draw the background of the map.
	
	// handling falling player
	// NOTE: i now realize that I cannot use the renderTexture becuase it does not take into
	// For this, we refer to player.cpp's vector2f fallPosition and draw everything from that point of view, so to speak, while the player falls.
	// we dont need to worry about changing how we draw entities and 3rd layer objects because they will be drawn ontop of the first two layers and if the 
	// player is behind the first two, it will be hidden from the third.
	// this can easily be done by updating that variable in collisionCheckVoid in player.cpp. then, we basically can draw the base layers of the map (1, 2)
	// once and then continue to draw the third layer continuously but from the pov of fallLocation vector2f.
	// NICE.
	int tSize = tileMap->tileSize;
	if (player->FLAG_FALL) {
		sf::Vector2f fallPosition = player->fallPos;
		sf::Vector2i intFallStart(static_cast<int>(fallPosition.x), static_cast<int>(fallPosition.y));
		sf::Vector2f lastSafePosition = player->lastSafePos;
		sf::IntRect fallDrawArea = tileMap->curDrawArea;
		int cSize = tileMap->chunkSize;
		
		sf::Vector2i mapDimChunk = tileMap->mapDimChunks;
		sf::Vector2i intTileStart(intFallStart.x / tSize, intFallStart.y / tSize);
		tileMap->mapTex.clear(sf::Color::Transparent);
		//tileMap->mapTex.draw(tileMap->bg);
		for (int y = fallDrawArea.top; y < fallDrawArea.top + fallDrawArea.height; y++) {
			for (int x = fallDrawArea.left; x < fallDrawArea.left + fallDrawArea.width; x++) {
				int curTile = tileMap->layer1Types[x + y * cSize * mapDimChunk.x];
				int curTile2 = tileMap->layer2Types[x + y * cSize * mapDimChunk.x];
				
				
				sf::Sprite tempSpr1(*tileMap->layer1Texture);
				tempSpr1.setTextureRect(sf::IntRect(0, curTile * tSize, tSize, tSize));
				tempSpr1.setPosition(sf::Vector2f(x * tSize, y * tSize));

				sf::Sprite tempSpr2(*tileMap->layer2Texture);
				tempSpr2.setTextureRect(sf::IntRect(0, curTile2 * tSize, tSize, tSize));
				tempSpr2.setPosition(sf::Vector2f(x * tSize, y * tSize));

				tileMap->mapTex.draw(tempSpr1);
				tileMap->mapTex.draw(tempSpr2);
				/*
				if (fallPosition.y < lastSafePosition.y) { // player fell facing away from camera
					if (x == fallDrawArea.left + fallDrawArea.width - 1 && y == intTileStart.y)
						tileMap->mapTex.draw(*player);
				}
				*/
				/*
				if (fallPosition.y > lastSafePosition.y) { // player fell facing towards the camera
					if (x == fallDrawArea.left + fallDrawArea.width - 1 && y == intTileStart.y)
						tileMap->mapTex.draw(*player);
				}
				else {
					if (x == fallDrawArea.left + fallDrawArea.width - 1 && y == intTileStart.y)
						tileMap->mapTex.draw(*player);
				}
				*/
				if (x == fallDrawArea.left + fallDrawArea.width - 1 && y == intTileStart.y)
					tileMap->mapTex.draw(*player);
			}
		}
		
	}
	else {
	// BASE LAYER:
	// we check if we need to update base map. the base map is made up of two layers, the "floor", and the "carpet" essentially.
		if (tileMap->checkForUpdate(player->getPosition())) {
			tileMap->updateTexMap();
			tileMap->updatePlayerChunk(player->getPosition());
		}
		
	}
	sf::Sprite mapSprite(tileMap->mapTex.getTexture());
	win.draw(mapSprite);

	// 3rd LAYER/ Interactable:		
	//						Like the lights, trees, chairs, doors and other things that go above
	//						the floor that can be interacted with.
	//						This layer also need to be drawn with the player and enemies because moving
	//						objects can go in front or behind the interactable tiles.
	sf::Vector2i mapDTiles = tileMap->getMapDimTiles();
	sf::IntRect thisDrawArea = tileMap->curDrawArea;
	sf::Vector2i playerPos(static_cast<int>(player->getPosition().x), static_cast<int>(player->getPosition().y));
	for (int y = thisDrawArea.top; y < thisDrawArea.height + thisDrawArea.top; y++) {
		for (int x = thisDrawArea.left; x < thisDrawArea.width + thisDrawArea.left; x++) {
			for (auto &i : eVec) {
				sf::Vector2i enemyPos(static_cast<int>(i.getPosition().x), static_cast<int>(i.getPosition().y));
				if ((enemyPos.y - enemyPos.y % tSize) / tSize == y && x == (thisDrawArea.width + thisDrawArea.left - 1)) {
					win.draw(i);
				}
				
			}
			if (!player->FLAG_FALL) {
				if ((playerPos.y - playerPos.y % tSize) / tSize == y && x == (thisDrawArea.width + thisDrawArea.left - 1)) {
					win.draw(*player);
				}
			}
			if (tileMap->layer3Types[x + y * mapDTiles.x] == 0)
				continue;
			else {
				sf::Sprite tempSpr(*tileMap->layer3Texture);
				// sf::Clock animTimer;???
				// use this animTimer to check if tiles should move to the next frame in the animation???
				// create a different class that uses sprites and Animation.h to animate different tiles
				
				// These are specific dimensioins for the interactable layer spriteSheet.
				// Later change this so that these tiles can be animated
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 1) {
					tempSpr.setTextureRect(tileMap->texDim1);
					tempSpr.setPosition(sf::Vector2f(x * tSize, y * tSize - 4));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 2) {
					tempSpr.setTextureRect(tileMap->texDim2);
					tempSpr.setPosition(sf::Vector2f(x * tSize, y * tSize - tSize - 2));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 3) {
					tempSpr.setTextureRect(tileMap->texDim3);
					tempSpr.setPosition(sf::Vector2f(x * tSize, y * tSize - tSize));
					win.draw(tempSpr);
				}
			}
		}
	}
	// 6th CANOPY LAYER:
		// MAYBE:
		// last, but not least, update the canopy layer
}

void Level::updateEnemies(float dt, sf::RenderWindow* win) {
	// maybe a for each loop is much faster, I am only using for loop because I want to be able to erase the enemies if necessary
	
	for (auto& e : eVec) {

		// always update the player distance size here so that it is properly handled
		e.distSize = sqrt(pow(player->getPosition().x - e.getPosition().x, 2)
			+ pow(player->getPosition().y - e.getPosition().y, 2));
		if (e.distSize > enemyRenderDistance) {
			continue;
		}
		else {
			if (player->attacking) {
				if (player->sword.checkHit(e.hitBox)) {
					e.getHit(player->sword.damage);
				}
			}
			if (e.distSize < enemyPlayerCollisionCheckDistance)
				player->collisionCheckEnemy(e.hitBox, e.damage);
			e.update(dt, player->getPosition(), tileMap, win);
		}
	}
	for (int i = 0; i < eVec.size(); i++) {
		if (eVec.at(i).FLAG_DEAD) {
			eVec.erase(eVec.begin() + i);
		}
	}
	/*
	for (int i = 0; i < eVec.size(); i++) {
		// always update the player distance size here so that it is properly handled
		eVec.at(i).distSize = sqrt(pow(player->getPosition().x - eVec.at(i).getPosition().x, 2)
			+ pow(player->getPosition().y - eVec.at(i).getPosition().x, 2));
		// check if the enemy in within a certain distance of player ya know?
		if (eVec.at(i).distSize < enemyRenderDistance) {
			continue;
		}
		eVec.at(i).update(dt, player->getPosition(), tileMap, win);
		if (eVec.at(i).FLAG_DEAD) {
			eVec.erase(eVec.begin() + i);
		}
	}
	*/
	/*
	for (auto& i : eVec) {
		i.update(dt, player->getPosition(), tileMap, win);
		if (i.FLAG_DEAD) {
			eVec.erase()
		}
	}
	*/
	// do the general updating of the level's enemies here. 
	// look into how I can use threads to update the areas' enemies.
}