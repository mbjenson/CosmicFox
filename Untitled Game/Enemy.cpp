#include "Enemy.h"

Enemy::Enemy(sf::Texture* spriteSheet, sf::Vector2u texDim, int _rowLength, int _rowNum, float _animTime) : 
	Entity( *spriteSheet, texDim, _rowLength, _rowNum, _animTime ) {}

bool Enemy::init() {

	FLAG_DEAD = false;

	setOrigin(sf::Vector2f(enemySize.x / 2, enemySize.y / 2));
	detectionRadius = 125.f;
	moveSpeed = 50;
	maxHealth = 5;
	curHealth = maxHealth;
	dampingFactor = 0;
	curRow = 0;
	hitBox = sf::FloatRect(0, 0, 16, 16);
	distSize = 0.f; 
	// init weapon
	curState = State::nominal;
	beingHit = false;
	// This one is default perhaps?
	//prevPlayerPos = sf::Vector2f(200, 200);
	return true;
}

void Enemy::collisionCheckTile(TileMap* map) {
	int i = 0;
	while (i < 2) {
		hitBox.left = getPosition().x - hitBox.width / 2;
		hitBox.top = getPosition().y - hitBox.height / 2;
		sf::FloatRect tempHitBox(hitBox.left + finalVel.x, hitBox.top + finalVel.y, hitBox.width, hitBox.height);
		bool TL, TR, BL, BR;
		//UPDATE CORNER BOOLS by passing in their location and checking if the tile they reside on is collidable

		if (tempHitBox.left < 0 || tempHitBox.left > map->getMapDimTiles().x * map->getTileSize())
			return;
		if (tempHitBox.top < 0 || tempHitBox.top > map->getMapDimTiles().y * map->getTileSize())
			return;
		if (tempHitBox.left + tempHitBox.width < 0 || tempHitBox.left + tempHitBox.width > map->getMapDimTiles().x * map->getTileSize())
			return;
		if (tempHitBox.top + tempHitBox.height < 0 || tempHitBox.top + tempHitBox.height > map->getMapDimTiles().y * map->getTileSize())
			return;

		// if top left corner intersects a collidable tile.
		if (map->getTileLogic(sf::Vector2f(tempHitBox.left, tempHitBox.top)) == 1)
			TL = true;
		else
			TL = false;
		// if top right intersects a collidable tile.
		if (map->getTileLogic(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top)) == 1)
			TR = true;
		else
			TR = false;
		// if bottom left intersects a collidable tile.
		if (map->getTileLogic(sf::Vector2f(tempHitBox.left, tempHitBox.top + tempHitBox.height)) == 1)
			BL = true;
		else
			BL = false;
		// if bottom right intersects a collidable tile.
		if (map->getTileLogic(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top + tempHitBox.height)) == 1)
			BR = true;
		else
			BR = false;

		// Corner cases involve corrected the player movement by the smaller distance(between x and y) to get out of tile bounds
		if (TL && !TR && !BL && !BR) {
			sf::Vector2f tilePos(map->getTilePos(sf::Vector2f(tempHitBox.left, tempHitBox.top)));
			//Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top));
			if ((tilePos.y + map->getTileSize()) - tempHitBox.top > (tilePos.x + map->getTileSize()) - tempHitBox.left) {
				finalVel.x = finalVel.x + ((tilePos.x + map->getTileSize()) - tempHitBox.left);
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y + ((tilePos.y + map->getTileSize()) - tempHitBox.top);
				// NOTE: when finished, remove moveDir.n = 0, this is already done
				moveDir.y = 0;
			}

		}
		if (TR && !TL && !BL && !BR) {
			sf::Vector2f tilePos = map->getTilePos(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top));
			if ((tilePos.y + map->getTileSize()) - tempHitBox.top > (tempHitBox.left + tempHitBox.width) - tilePos.x) {
				finalVel.x = finalVel.x - ((tempHitBox.left + tempHitBox.width) - tilePos.x);
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y + ((tilePos.y + map->getTileSize()) - tempHitBox.top);
				moveDir.y = 0;
			}

		}
		if (BR && !TL && !BL && !TR) {
			sf::Vector2f tilePos = map->getTilePos(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top + tempHitBox.height));
			if ((tempHitBox.top + tempHitBox.height) - tilePos.y > (tempHitBox.left + tempHitBox.width) - tilePos.x) {
				finalVel.x = finalVel.x - ((tempHitBox.left + tempHitBox.width) - tilePos.x);
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - tilePos.y);
				moveDir.y = 0;
			}

		}
		if (BL && !TL && !TR && !BR) {
			sf::Vector2f tilePos = map->getTilePos(sf::Vector2f(tempHitBox.left, tempHitBox.top + tempHitBox.height));
			if ((tempHitBox.top + tempHitBox.height) - tilePos.y > (tilePos.x + map->getTileSize()) - tempHitBox.left) {
				finalVel.x = finalVel.x - (tempHitBox.left - (tilePos.x + map->getTileSize()));
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - tilePos.y);
				moveDir.y = 0;
			}

		}
		if (TR && BR) {
			sf::Vector2f tilePos = map->getTilePos(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top));
			finalVel.x = finalVel.x + (tilePos.x - (tempHitBox.left + tempHitBox.width));

		}
		if (TL && BL) {
			sf::Vector2f tilePos = map->getTilePos(sf::Vector2f(tempHitBox.left, tempHitBox.top));
			finalVel.x = finalVel.x + ((tilePos.x + map->getTileSize()) - tempHitBox.left);

		}
		if (TL && TR) {
			sf::Vector2f tilePos = map->getTilePos(sf::Vector2f(tempHitBox.left, tempHitBox.top));
			finalVel.y = finalVel.y + ((tilePos.y + map->getTileSize()) - tempHitBox.top);

		}
		if (BL && BR) {
			sf::Vector2f tilePos = map->getTilePos(sf::Vector2f(tempHitBox.left, tempHitBox.top + tempHitBox.height));
			finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - tilePos.y);

		}
		i++;
	}
	
}

void Enemy::setSpawn(sf::Vector2f _spawnpoint) {
	spawnpoint = _spawnpoint;
}

void Enemy::update(float deltaTime, sf::Vector2f playerPos, TileMap* map, sf::RenderWindow* win) {

	// use the calculated value for the enemycollisionvector to move the player slightly

	curRow = static_cast<int>(getPosition().y) / map->tileSize;
	sf::Vector2f distVec(playerPos.x - getPosition().x, playerPos.y - getPosition().y);
	//distSize = sqrt(pow(distVec.x, 2) + pow(distVec.y, 2));
	playerDirNormal = sf::Vector2f(distVec.x / distSize, distVec.y / distSize);

	switch (curState) {
	case State::nominal:
	{
		tSprite.setColor(stdCol);
		basicMovement(playerPos, distVec, distSize, deltaTime);
		break;
		//move(finalVel);
	}
	case State::attacked:
		
		if (stunClock.getElapsedTime().asMilliseconds() > totalHitTime) {
			beingHit = false;
			curState = State::nominal; // this is a crappy way to do this. but for now its fine.
		}
		if (stunClock.getElapsedTime().asMilliseconds() < hitBackTime) {
			// how do big games manage entities. Each one with different information. Each one different sword size, different specs... BHV!
			// my temp fix for moving the player away when hes hit is to hard code the radius of the sword and get the distance from outer edge.
			// playerSwordRadiusSize - distSize;
			// then the amount the player moves is proportional to how close the enemy is to the player.
			// the closer the more it moves

			float tempHitSpeed = pow((hitBackSpeed / (distSize)), 2) * 3; // old 4
			tSprite.setColor(sf::Color::Red);
			finalVel = sf::Vector2f(deltaTime * hitVector.x * tempHitSpeed, deltaTime * hitVector.y * tempHitSpeed);
		}
		if (stunClock.getElapsedTime().asMilliseconds() > hitBackTime) {
			

			tSprite.setColor(stdCol);
		}
		
		// stun:
		if (stunClock.getElapsedTime().asMilliseconds() < totalHitTime) {
			//finalVel.x -= finalVel.x * 0.1;
			//finalVel.y -= finalVel.y * 0.1;
			break;
		}
	}
	
	// update Animations:
	setAnimations();
	// collision checks
	collisionCheckTile(map);
	// CollisionCheckEnemy is done in level file
	// final vel
	move(finalVel);
	//prevPlayerPos = playerPos;
	updateAnim();
}

void Enemy::getHit(int damage) {
	if (curHealth <= 0)
		FLAG_DEAD = true;
	if (!beingHit)
		curHealth -= damage;
	beingHit = true;
	stunClock.restart();
	curState = State::attacked;
	// hit vector is oposite direction from the player
	hitVector = sf::Vector2f(playerDirNormal.x * -1, playerDirNormal.y * -1);
}

void Enemy::revive() {
	FLAG_DEAD = false;
	setPosition(spawnpoint);
}