#include "Player.h"

Player::Player(	sf::Texture& texture, sf::RenderWindow& win, sf::Vector2u textureDim, 
				int rowLength, int rowNumber, float animationTime) :
		Entity( texture, textureDim, rowLength, rowNumber, animationTime)
{
	pWindow = &win;
	setOrigin(sf::Vector2f(hitBoxSize.x / 2, hitBoxSize.y / 2));
	setPosition(sf::Vector2f(0, 0)); // starting position
	hitBox = sf::FloatRect(getPosition().x - hitBoxSize.x / 2, getPosition().y - hitBoxSize.y / 2, hitBoxSize.x, hitBoxSize.y); // init hitbox
}

void Player::update(float deltaTime, TileMap* map) {
	//getKeyPresses();
	switch (state) {
		// nominal = walking or idle
		case State::nominal:
			if (upPressed)
				walkNorth();
			if (downPressed)
				walkSouth();
			if (leftPressed)
				walkWest();
			if (rightPressed)
				walkEast();
			normalizeWalkVel();
			walkVelocity += moveDir * walkSpeed * deltaTime;
			finalVel = walkVelocity;
			moveDir = sf::Vector2f(0, 0);
			applyWalkFriction();

			updateTrav();
			setDiagBool();

			updatePlayerTile(map);
			collisionCheckTile(map);
			//collisionCheckEnemy();
			//collisionCheckSpace();
			//collisionCheckSomeotherthing();
			move(finalVel);
			// handle animations in here aswell
			// so if left then walk left animation
			break;
		case State::cooldown: // cooldown from dashing
			// if dashtime > total dashtime as microseconds
			// dash time = 0 and state = walking
			break;
		case State::dashing:
			// if state = dashing then 
			// set movment velocity much higher for a short time
			break;

		case State::deactivated:
			break;
		case State::dead:
			break;
		case State::invulnerable:
			break;
	}
	// finally move the player to new position
	
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
	// trav bools
	travNorth = false; travSouth = false; travEast = false; travWest = false; travDiag = false;
	dashEast = false; dashWest = false; dashSouth = false; dashNorth = false;
	// key press bools
	spacePressed = false; upPressed = false; downPressed = false; leftPressed = false;
	rightPressed = false; escapePressed = false;
}

// takes position (middle of player) and calculates the top and left coord of hitbox
void Player::updateHitBox()
{
	hitBox.left = getPosition().x - hitBoxSize.x / 2;
	hitBox.top = getPosition().y - hitBoxSize.y / 2;
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

// put a piecewise function in here that takes a frame number and performs an acceleration on the players velocity for a breif moment
//	then, after the breif moment, a.k.a the frame number is greater than allowed for breif dash, perform a cooldown time that takes the number and does
//		nothing to the velocity;
// BAD FUNCTION DOESN'T WORK
void Player::dash(float curTime, float deltaTime) {
	// simply set the players velocity to a set amount when space is pressed
	if (curTime - dashCooldown > dashTimeStart) {
		dashTimeStart = curTime;
	}
	if (curTime - dashCooldown < dashTimeStart){
		if (curTime < dashTimeStart + dashCooldown) {
			if (travSouth) {
				if (travEast) {
					dashVel.y = dashAcc * deltaTime * 0.7071;
					dashVel.x = dashAcc * deltaTime * 0.7071;
					return;
				}
				if (travWest) {
					dashVel.y = dashAcc * deltaTime * 0.7071;
					dashVel.x = -dashAcc * deltaTime * 0.7071;
					return;
				}
				else {
					dashVel.y = dashAcc * deltaTime;
					return;
				}
			}
			if (travNorth) {
				if (travEast) {
					dashVel.y = -dashAcc * deltaTime * 0.7071;
					dashVel.x = dashAcc * deltaTime * 0.7071;
					return;
				}
				if (travWest) {
					dashVel.y = -dashAcc * deltaTime * 0.7071;
					dashVel.x = -dashAcc * deltaTime * 0.7071;
					return;
				}
				else {
					dashVel.y = -dashAcc * deltaTime;
					return;
				}
			}
			if (travEast) {
				dashVel.x = dashAcc * deltaTime;
				return;
			}
			if (travWest) {
				dashVel.x = -dashAcc * deltaTime;
				return;
			}
		}
	}
}

// the xxAnim() functions will update the row that the animation updates from in the sprite sheet
void Player::wLeftAnim() {
	Animation::updateRow(wLeftAnimDim.y, wLeftAnimDim.y);
}
void Player::wRightAnim() {
	Animation::updateRow(wRightAnimDim.y, wRightAnimDim.x);
}
void Player::wUpAnim() {
	Animation::updateRow(wUpAnimDim.y, wUpAnimDim.x);
}
void Player::wDownAnim() {
	Animation::updateRow(wDownAnimDim.y, wDownAnimDim.x);
}
void Player::idleDownAnim() {
	Animation::updateRow(idleDownAnimDim.y, idleDownAnimDim.x);
}
void Player::idleUpAnim() {
	Animation::updateRow(idleUpAnimDim.y, idleUpAnimDim.x);
}
void Player::idleLeftAnim() {
	Animation::updateRow(idleLeftAnimDim.y, idleLeftAnimDim.x);
}
void Player::idleRightAnim() {
	Animation::updateRow(idleRightAnimDim.y, idleRightAnimDim.x);
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
// NOTE: ??maybelater I will take a level object and check for collision there?
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

sf::Vector2f Player::getWlkVel() {
	return walkVelocity;
}

sf::Vector2f Player::getFinalVel() {
	return finalVel;
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