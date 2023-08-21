#include "Level.h"

void Level::render(sf::RenderWindow& win) {
	
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
	//						Like the trees ad other things that go above
	//						the floor that can walked around.

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
			if (player->FLAG_DEAD) {
				if ((playerPos.y - playerPos.y % tSize) / tSize == y && (playerPos.x - playerPos.x % tSize) / tSize == x) {
					win.draw(*player);
				}
			}
			
			/*
			if (!player->FLAG_FALL) {
				if ((playerPos.y - playerPos.y % tSize) / tSize == y && x == ((playerPos.x - playerPos.x % tSize) / tSize))
					win.draw(*player);
			}
			*/
			if (tileMap->layer3Types[x + y * mapDTiles.x] == 0)
				continue;
			else {
				sf::Sprite tempSpr(*tileMap->layer3Texture);
				
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 1) {
					tempSpr.setTextureRect(tileMap->texDim1);
					tempSpr.setPosition(sf::Vector2f(x * tSize - tileMap->offsetDim1.x, y * tSize - tileMap->offsetDim1.y));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 2) {
					tempSpr.setTextureRect(tileMap->texDim2);
					tempSpr.setPosition(sf::Vector2f(x * tSize - tileMap->offsetDim2.x, y * tSize - tileMap->offsetDim2.y));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 3) {
					tempSpr.setTextureRect(tileMap->texDim3);
					tempSpr.setPosition(sf::Vector2f(x * tSize - tileMap->offsetDim3.x, y * tSize - tileMap->offsetDim3.y));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 4) {
					tempSpr.setTextureRect(tileMap->texDim4);
					tempSpr.setPosition(sf::Vector2f(x* tSize - tileMap->offsetDim4.x, y* tSize - tileMap->offsetDim4.y));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 5) {
					tempSpr.setTextureRect(tileMap->texDim5);
					tempSpr.setPosition(sf::Vector2f(x * tSize - tileMap->offsetDim5.x, y * tSize - tileMap->offsetDim5.y));
					win.draw(tempSpr);
				}
				if (tileMap->layer3Types[x + y * mapDTiles.x] == 6) {
					tempSpr.setTextureRect(tileMap->texDim6);
					tempSpr.setPosition(sf::Vector2f(x * tSize - tileMap->offsetDim6.x, y * tSize - tileMap->offsetDim6.y));
					win.draw(tempSpr);
				}
				
			}
		}
	}
	if (usingShader) {
		win.draw(mapMask, &shader);
	}
}

void Level::updateEnemies(float dt, sf::RenderWindow* win) {

	if (hasEnemies) {
		// spawn enemies
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
				if (s1.Playing) {
					s1.play();
				}



			}
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