#include "Player.h"

Player::Player(	sf::Texture& texture, sf::RenderWindow& win, sf::Vector2u textureDim, 
				int rowLength, int rowNumber, float animationTime) :
		Entity( texture, textureDim, rowLength, rowNumber, animationTime)
{
	pWindow = &win;
}
/*
void Player::update(float deltaTime, TileMap* map) {
	//getKeyPresses();
	
	moveDir = sf::Vector2f(0, 0);
	switch (state) {
		// nominal = walking or idle
		case State::nominal:
			if (upPressed) {
				walkNorth();
			}
			if (downPressed) {
				walkSouth();
			}
			if (leftPressed) {
				walkWest();
			}
			if (rightPressed) {
				walkEast();
			}
			//issue: attacking only updatees when LMB pressed
			if (LMBPressed) {
				attacking = true;
			}
			if (attacking) {
				attacking = sword.swing(*pWindow);
			}
			if (spacePressed) 
				setState(State::dashing);
			if (isDashing)
				setState(State::dashing);
			else
				dashVel = sf::Vector2f(0, 0);

			setFacing();
			setAnimation();
			// calculates the walking velocity and only applies it here if the state has not changed.
			normalizeWalkVel();
			walkVelocity = moveDir * walkSpeed * deltaTime;
			//applyWalkFriction();
			// * walkVelocity is now packed and ready for shipment... *
			updateTrav();
			if (state == State::nominal) {
				finalVel = walkVelocity;
				collisionCheckTile(map);
				move(finalVel);
				// walking or idle animations here
				break;
			}
		//case State::cooldown: // cooldown from dashing or something else
			
		case State::dashing:
			// IF ERROR THEN CHANGE BACK:
			// ** NOTE: replaced the dashTimer.getElapsed times with curDashTimer
			int curDashTimer = dashTimer.getElapsedTime().asMilliseconds();
			// protect from integer overflow
			if (curDashTimer > 300000000) {
				dashTimer.restart();
			}
			// *if player has passed cooldown
			if (curDashTimer > dashCooldown) {
				dashTimer.restart();
				
				if (moveDir.x == 0 && moveDir.y == 0) {
					prepDashVel = lastFacing;
				}
				else {
					prepDashVel = moveDir;
				}
				
				//prepDashVel = moveDir;
			}
			// *checking if the speed should be increased
			if (curDashTimer < dashSpeedTime) {
				
				dashVel.x = prepDashVel.x * deltaTime * dashSpeed;
				dashVel.y = prepDashVel.y * deltaTime * dashSpeed;
				finalVel = walkVelocity + dashVel;
				collisionCheckTile(map);
				move(finalVel);
				isDashing = true;
			}
			// if we hit a wall, dashing stops
			if (dashVel.x == 0 && dashVel.y == 0)
				isDashing = false;
			// *if in dash cooldown phase
			if (curDashTimer > dashSpeedTime && curDashTimer < dashCooldown) {
				finalVel = walkVelocity;
				collisionCheckTile(map);
				move(finalVel);
				isDashing = false;
				setState(State::nominal);
			}
			else {
				isDashing = true;
				setState(State::nominal);
			}
			
			// if state = dashing then 
			// have a dash clock that is local to the player class, everytime you are able to dash you update the dash class
			// if dashtime > total dashtime as microseconds
			// dash time = 0 and state = walking
			
		//case State::deactivated:
			
		//case State::dead:
			
		//case State::invulnerable:
	}
	// finally, update the player's position on the map
	sword.updatePos(getPosition());
	updateAnim();
	updatePlayerTile(map);
}
*/
void Player::update(float deltaTime, TileMapmk2* map) {
	//getKeyPresses();

	moveDir = sf::Vector2f(0, 0);
	switch (state) {
		// nominal = walking or idle
	case State::nominal:
		if (upPressed) {
			walkNorth();
		}
		if (downPressed) {
			walkSouth();
		}
		if (leftPressed) {
			walkWest();
		}
		if (rightPressed) {
			walkEast();
		}
		if (LMBPressed) {
			attacking = true;
		}
		if (attacking) {
			attacking = sword.swing(*pWindow);
		}
		if (spacePressed)
			setState(State::dashing);
		if (isDashing)
			setState(State::dashing);
		else
			dashVel = sf::Vector2f(0, 0);

		setFacing();
		setAnimation();
		// calculates the walking velocity and only applies it here if the state has not changed.
		normalizeWalkVel();
		walkVelocity = moveDir * walkSpeed * deltaTime;
		//applyWalkFriction();
		// * walkVelocity is now packed and ready for shipment... *
		updateTrav();
		if (state == State::nominal) {
			finalVel = walkVelocity;
			collisionCheckTile(map);
			move(finalVel);
			// walking or idle animations here
			break;
		}
		//case State::cooldown: // cooldown from dashing or something else

	case State::dashing:
		// IF ERROR THEN CHANGE BACK:
		// ** NOTE: replaced the dashTimer.getElapsed times with curDashTimer
		int curDashTimer = dashTimer.getElapsedTime().asMilliseconds();
		// protect from integer overflow
		if (curDashTimer > 300000000) {
			dashTimer.restart();
		}
		// *if player has passed cooldown
		if (curDashTimer > dashCooldown) {
			dashTimer.restart();

			if (moveDir.x == 0 && moveDir.y == 0) {
				prepDashVel = lastFacing;
			}
			else {
				prepDashVel = moveDir;
			}

			//prepDashVel = moveDir;
		}
		// *checking if the speed should be increased
		if (curDashTimer < dashSpeedTime) {

			dashVel.x = prepDashVel.x * deltaTime * dashSpeed;
			dashVel.y = prepDashVel.y * deltaTime * dashSpeed;
			finalVel = walkVelocity + dashVel;
			collisionCheckTile(map);
			move(finalVel);
			isDashing = true;
		}
		// if we hit a wall, dashing stops
		if (dashVel.x == 0 && dashVel.y == 0)
			isDashing = false;
		// *if in dash cooldown phase
		if (curDashTimer > dashSpeedTime && curDashTimer < dashCooldown) {
			finalVel = walkVelocity;
			collisionCheckTile(map);
			move(finalVel);
			isDashing = false;
			setState(State::nominal);
		}
		else {
			isDashing = true;
			setState(State::nominal);
		}

		// if state = dashing then 
		// have a dash clock that is local to the player class, everytime you are able to dash you update the dash class
		// if dashtime > total dashtime as microseconds
		// dash time = 0 and state = walking

	//case State::deactivated:

	//case State::dead:

	//case State::invulnerable:
	}
	// finally, update the player's position on the map
	sword.updatePos(getPosition());
	updateAnim();
	
}

void Player::setAnimation() {
	// horizontal movement has priority over vertical movement
	if (moveDir.x == 0 && moveDir.y == 0) {
		if (lastFacing.x == 1) {
			idleRightAnim();
			return;
		}
		if (lastFacing.x == -1) {
			idleLeftAnim();
			return;
		}
		if (lastFacing.y == 1) {
			idleDownAnim();
			return;
		}
		if (lastFacing.y == -1) {
			idleUpAnim();
			return;
		}
	}
	if (lastFacing.x == 1) {
		wRightAnim();
		return;
	}
	if (lastFacing.x == -1) {
		wLeftAnim();
		return;
	}
	if (lastFacing.y == -1) {
		wUpAnim();
		return;
	}
	if (lastFacing.y == 1) {
		wDownAnim();
		return;
	}
}

void Player::setFacing() {
	// if I am travelling north and add an eastward movement we now move east
	if (moveDir.x == 1 && moveDir.y == 0) {
		lastFacing.x = 1;
		lastFacing.y = 0;
	}
	if (moveDir.x == -1 && moveDir.y == 0) {
		lastFacing.x = -1;
		lastFacing.y = 0;
	}
	if (moveDir.y == 1 && moveDir.x == 0) {
		lastFacing.y = 1;
		lastFacing.x = 0;
	}
	if (moveDir.y == -1 && moveDir.x == 0) {
		lastFacing.y = -1;
		lastFacing.x = 0;
	}
	// if two inputs are given we will favor the x
	if (moveDir.x == 1 && moveDir.y != 0) {
		lastFacing.x = 1;
		lastFacing.y = 0;
	}
	if (moveDir.x == -1 && moveDir.y != 0) {
		lastFacing.x = -1;
		lastFacing.y = 0;
	}
	// use last facing if current dir is not anything
}

void Player::normalizeWalkVel() {
	float velVector = sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2));
	if (velVector > 1.f) {
		moveDir.x = moveDir.x / velVector;
		moveDir.y = moveDir.y / velVector;
	}
}

void Player::applyWalkFriction() {
	if (travEast)
		walkVelocity.x -= walkVelocity.x * kinFrictionCoef;
	if (travWest)
		walkVelocity.x += -walkVelocity.x * kinFrictionCoef;
	if (travSouth)
		walkVelocity.y -= walkVelocity.y * kinFrictionCoef;
	if (travNorth)
		walkVelocity.y += -walkVelocity.y * kinFrictionCoef;
}

void Player::setState(State _state) {
	Player::state = _state;
}

void Player::setDiagBool() {
	if ((travNorth && travEast) || (travNorth && travWest) || (travSouth && travEast) || (travSouth && travWest))
		travDiag = true;
	else
		travDiag = false;
}

//here I will set the values of the animation dims and other specs for the player like giving dirbools initial values
void Player::init() {
	setHitBoxSize(sf::Vector2f(8.f, 8.f), sf::Vector2f(3.f, 6.f));

	setOrigin(sf::Vector2f(8, 8));
	// trav bools
	travNorth = false; travSouth = false; travEast = false; travWest = false; travDiag = false;
	dashEast = false; dashWest = false; dashSouth = false; dashNorth = false;
	// key press bools
	spacePressed = false; upPressed = false; downPressed = false; leftPressed = false;
	rightPressed = false;
	dashVel = sf::Vector2f(0, 0);
	// row num and row len
	idleDownAnimDim = sf::Vector2u(8, 0);
	wRightAnimDim = sf::Vector2u(8, 1);
	wLeftAnimDim = sf::Vector2u(8, 2);
	wUpAnimDim = sf::Vector2u(8, 3);
	wDownAnimDim = sf::Vector2u(8, 4);
	idleLeftAnimDim = sf::Vector2u(8, 5);
	idleRightAnimDim = sf::Vector2u(8, 6);
	idleUpAnimDim = sf::Vector2u(6, 7);
	//sword settup
	swordTex.loadFromFile("Textures/slash1.png");
	sword = Sword(swordTex, sf::Vector2u(32, 16), 1, 0, 0.f);
	sword.initSword();
}

void Player::setHitBoxSize(sf::Vector2f size, sf::Vector2f offset) {
	hitBox.width = size.x;
	hitBox.height = size.y;
	hitBoxOffset.x = offset.x;
	hitBoxOffset.y = offset.y;
}
// takes position (middle of player) and calculates the top and left coord of hitbox rect
/*
void Player::updateHitBox() {
	hitBox.left = getPosition().x - hitBoxSize.x / 2 + hitBoxOffset.x;
	hitBox.top = getPosition().y - hitBoxSize.y / 2 + hitBoxOffset.y;
}
*/

void Player::updateHitBox() {
	hitBox.left = getPosition().x - hitBox.width / 2;// + hitBoxOffset.x;
	hitBox.top = getPosition().y - hitBox.height / 2 + hitBoxOffset.y;// +hitBoxOffset.y;
}

void Player::walkNorth() {
	if (northAllowed)
	{
		moveDir.y = -1;
	}
}

void Player::walkEast() {
	if (eastAllowed)
	{
		moveDir.x = 1;
	}
}

void Player::walkSouth() {
	if (southAllowed)
	{
		moveDir.y = 1;
	}
}

void Player::walkWest() {
	if (westAllowed)
	{
		moveDir.x = -1;
	}
}

// the xxAnim() functions will update the row that the animation updates from in the sprite sheet
void Player::wLeftAnim() {
	Player::Animation::updateRow(wLeftAnimDim.y, wLeftAnimDim.x);
}
void Player::wRightAnim() {
	Player::Animation::updateRow(wRightAnimDim.y, wRightAnimDim.x);
}
void Player::wUpAnim() {
	Player::Animation::updateRow(wUpAnimDim.y, wUpAnimDim.x);
}
void Player::wDownAnim() {
	Player::Animation::updateRow(wDownAnimDim.y, wDownAnimDim.x);
}
void Player::idleDownAnim() {
	Player::Animation::updateRow(idleDownAnimDim.y, idleDownAnimDim.x);
}
void Player::idleUpAnim() {
	Player::Animation::updateRow(idleUpAnimDim.y, idleUpAnimDim.x);
}
void Player::idleLeftAnim() {
	Player::Animation::updateRow(idleLeftAnimDim.y, idleLeftAnimDim.x);
}
void Player::idleRightAnim() {
	Player::Animation::updateRow(idleRightAnimDim.y, idleRightAnimDim.x);
}
void Player::dashLeftAnim() {
	Animation::updateRow(dashLeftAnimDim.y, dashLeftAnimDim.x);
}
void Player::dashRightAnim() {
	Animation::updateRow(dashRightAnimDim.y, dashRightAnimDim.x);
}
void Player::dashUpAnim() {
	Animation::updateRow(dashUpAnimDim.y, dashUpAnimDim.x);
}
void Player::dashDownAnim() {
	Animation::updateRow(dashDownAnimDim.y, dashDownAnimDim.x);
}

void Player::updateTrav() {
	//sf::Vector2f rndVel(floor(wlkVel.x / 1), floor(wlkVel.y / 1));
	if (finalVel.y < 0)
		travNorth = true;
	else
		travNorth = false;
	if (finalVel.y > 0)
		travSouth = true;
	else
		travSouth = false;
	if (finalVel.x > 0)
		travEast = true;
	else
		travEast = false;
	if (finalVel.x < 0)
		travWest = true;
	else
		travWest = false;
}

// updates player's rotation to face the mouse
void Player::updateRotMouse()
{
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*pWindow);
	sf::Vector2f mouseWorldPos = pWindow->mapPixelToCoords(mousePixelPos, pWindow->getView());

	float dX = mouseWorldPos.x - getPosition().x;
	float dY = mouseWorldPos.y - getPosition().y;
	float thisAngle = (atan2(dY, dX) * 180.f) / 3.14159f;
	setRotation(thisAngle+90);
}

// updates the player's current tile
void Player::updatePlayerTile(TileMap* map) // update the curTile var for given map in index form
{
	curTile = sf::Vector2i(int(floor(getPosition().x / map->tileSize.x)), int(floor(getPosition().y / map->tileSize.y)));
}

// check for collision with collidable tiles in tilemap
/*
void Player::collisionCheckTile(TileMap* map) {
	int i = 0;
	while (i < 2) {
		updateHitBox();
		sf::FloatRect tempHitBox(hitBox.left + finalVel.x, hitBox.top + finalVel.y, hitBox.width, hitBox.height);
		bool TL, TR, BL, BR;
		//UPDATE CORNER BOOLS by passing in their location and checking if the tile they reside on is collidable

		if (tempHitBox.left < 0 || tempHitBox.left > map->mapSize.x * map->tileSize.x)
			return;
		if (tempHitBox.top < 0 || tempHitBox.top > map->mapSize.y * map->tileSize.y)
			return;
		if (tempHitBox.left + tempHitBox.width < 0 || tempHitBox.left + tempHitBox.width > map->mapSize.x * map->tileSize.x)
			return;
		if (tempHitBox.top + tempHitBox.height < 0 || tempHitBox.top + tempHitBox.height > map->mapSize.y * map->tileSize.y)
			return;

		// if top left corner intersects a collidable tile.
		if (map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top)).collidable)
			TL = true;
		else
			TL = false;
		// if top right intersects a collidable tile.
		if (map->getTileWithPoints(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top)).collidable)
			TR = true;
		else
			TR = false;
		// if bottom left intersects a collidable tile.
		if (map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top + tempHitBox.height)).collidable)
			BL = true;
		else
			BL = false;
		// if bottom right intersects a collidable tile.
		if (map->getTileWithPoints(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top + tempHitBox.height)).collidable)
			BR = true;
		else
			BR = false;

		// Corner cases involve corrected the player movement by the smaller distance(between x and y) to get out of tile bounds
		if (TL && !TR && !BL && !BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top));
			if ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top > (thisTile.getPosition().x + map->tileSize.x) - tempHitBox.left) {
				finalVel.x = finalVel.x + ((thisTile.getPosition().x + map->tileSize.x) - tempHitBox.left);
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y + ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top);
				moveDir.y = 0;
			}
		}
		if (TR && !TL && !BL && !BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top));
			if ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top > (tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x) {
				finalVel.x = finalVel.x - ((tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x);
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y + ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top);
				moveDir.y = 0;
			}
		}
		if (BR && !TL && !BL && !TR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top + tempHitBox.height));
			if ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y > (tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x) {
				finalVel.x = finalVel.x - ((tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x);
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y);
				moveDir.y = 0;
			}
		}
		if (BL && !TL && !TR && !BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top + tempHitBox.height));
			if ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y > (thisTile.getPosition().x + map->tileSize.x) - tempHitBox.left) {
				finalVel.x = finalVel.x - (tempHitBox.left - (thisTile.getPosition().x + map->tileSize.x));
				moveDir.x = 0;
			}
			else {
				finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y);
				moveDir.y = 0;
			}
		}
		if (TR && BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top));
			finalVel.x = finalVel.x + (thisTile.getPosition().x - (tempHitBox.left + tempHitBox.width));
		}
		if (TL && BL) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top));
			finalVel.x = finalVel.x + ((thisTile.getPosition().x + map->tileSize.x) - tempHitBox.left);
		}
		if (TL && TR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top));
			finalVel.y = finalVel.y + ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top);
		}
		if (BL && BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top + tempHitBox.height));
			finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y);
		}
		i++;
	}
}
*/
void Player::collisionCheckTile(TileMapmk2* map) {
	int i = 0;
	while (i < 2) {
		updateHitBox();
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

sf::Vector2f Player::getWlkVel() {
	return walkVelocity;
}

sf::Vector2f Player::getFinalVel() {
	return finalVel;
}

sf::Vector2f Player::getDashVel() {
	return dashVel;
}

int Player::getDashTimer() {
	return dashTimer.getElapsedTime().asMilliseconds();
}

sf::Vector2f Player::getFacing() {
	return lastFacing;
}

void Player::updatePWindow(sf::RenderWindow& win) {
	pWindow = &win;
}


//THE FOLLOWING ARE RELATIVELY USELESS FUNCTIONS just keeping for good measure
/*
* // updates angle using Directions
void Player::updateDir() {
	if (travEast) {
		if (travSouth) {
			playerAngle = 315;
		}
		else if (travNorth) {
			playerAngle = 45;
		}
		else {
			playerAngle = 0;
		}
	}
	if (travWest) {
		if (travSouth) {
			playerAngle = 225;
		}
		else if (travNorth) {
			playerAngle = 135;
		}
		else {
			playerAngle = 180;
		}
	}
	if (travNorth)
		playerAngle = 90;

	if (travSouth)
		playerAngle = 270;
}
*/
/*
// updates player's rotation to face the direction it is travelling

void Player::updateMovementAngle() {
	if (travEast & !travWest & !travSouth & !travNorth)
		movementAngle = 90;
	if (travWest & !travEast & !travSouth & !travNorth)
		movementAngle = 270;
	if (travSouth & !travWest & !travEast & !travNorth)
		movementAngle = 180;
	if (travNorth & !travWest & !travSouth & !travEast)
		movementAngle = 0;

	if (travNorth & travEast & !travSouth & !travWest)
		movementAngle = 45;
	if (travNorth & travWest & !travSouth & !travEast)
		movementAngle = 315;
	if (travSouth & travWest & !travNorth & !travEast)
		movementAngle = 225;
	if (travSouth & travEast & !travNorth & !travWest)
		movementAngle = 135;
}
*/
/*
void Player::updateRot() {

	setRotation(movementAngle);

}
*/
/*
void Player::updateMovement(float deltaTime, TileMap* map)
{
	updateTrav();
	updateMovementAngle();


	applyFriction();

	finalVel = sf::Vector2f(wlkVel);
	collisionCheck(map);
	move(finalVel);
}
*/