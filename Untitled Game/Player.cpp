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

	updatePlayerTile(map);
	updateDir();
	updateMovementAngle();
	// update direction player is facing
	switch (state) {
		// nominal is walking or idle
		case State::nominal:
			if (upPressed)
				walkNorth(deltaTime);
			if (downPressed)
				walkSouth(deltaTime);
			if (leftPressed)
				walkWest(deltaTime);
			if (rightPressed)
				walkEast(deltaTime);
			limWalkVel();
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
			// 
			break;

		case State::deactivated:
			break;
		case State::dead:
			break;
		case State::invulnerable:
			break;
	}
	applyFriction();
	finalVel = sf::Vector2f(wlkVel);
	collisionCheck(map);
	//collisionCheckEnemy();
	//collisionCheckSpace();
	//collisionCheckSomeotherthing();
	
	move(finalVel);
	// finally move the player to new position

}

void Player::updateMovement(float deltaTime, TileMap* map)
{
	updateDir();
	updateMovementAngle();

	limWalkVel();
	applyFriction();

	finalVel = sf::Vector2f(wlkVel + dashVel);
	collisionCheck(map);
	move(finalVel);
}

void Player::setState(State _state) {
	Player::state = _state;
}

void Player::getKeyPresses(bool up, bool down, bool left, bool right, bool space, bool esc) {
	
}



//here I will set the values of the animation dims and other specs for the player like giving dirbools initial values
void Player::init() {
	// trav bools
	travNorth = false; travSouth = false; travEast = false; travWest = false;
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

void Player::walkNorth(float deltaTime) {
	if (northAllowed)
	{
		//deltaVel.y = -1;
		wlkVel.y -= deltaTime * wlkAcc;
	}
}

void Player::walkEast(float deltaTime) {
	if (eastAllowed)
	{
		//deltaVel.x = 1;
		wlkVel.x += deltaTime * wlkAcc;
	}
}

void Player::walkSouth(float deltaTime) {
	if (southAllowed)
	{
		//deltaVel.y = 1;
		wlkVel.y += deltaTime * wlkAcc;
	}
}

void Player::walkWest(float deltaTime) {
	if (westAllowed)
	{
		//deltaVel.x = -1;
		wlkVel.x -= deltaTime * wlkAcc;
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

void Player::limitDashVel() {
	return;
}

void Player::limWalkVel() {
	//	check which direction the player is traveling
	//if traveling straight 
	//	check if velocity is > max velocity
	//	if so, subtract the difference between the players current velocity and the maximum velocity
	//if traveling in two directions
	//	check if the velocity is > max velocity * 45 degrees
	//	if so , subtract the differece between the players current velocity and the maximum velocity * 45 degrees

	if (travSouth) {
		if (wlkVel.y > maxWlkVel)
			wlkVel.y -= (wlkVel.y - maxWlkVel);
	}
	if (travNorth) {
		if (wlkVel.y < -maxWlkVel)
			wlkVel.y += (-wlkVel.y - maxWlkVel);
	}
	if (travEast) {
		if (wlkVel.x > maxWlkVel)
			wlkVel.x -= (wlkVel.x - maxWlkVel);
	}
	if (travWest) {
		if (wlkVel.x < -maxWlkVel)
			wlkVel.x += (-wlkVel.x - maxWlkVel);
	}
	
	float angle = atan2(wlkVel.x, wlkVel.y);
	float dirYMax = maxWlkVel * cos(angle);
	float dirXMax = maxWlkVel * sin(angle);

	if (travSouth && travEast) {
		if (wlkVel.y > dirYMax && wlkVel.x > dirXMax) {
			wlkVel.y -= (wlkVel.y - dirYMax);
			wlkVel.x -= (wlkVel.x - dirXMax);
		}
	}
	if (travNorth && travEast) {
		if (wlkVel.y < dirYMax && wlkVel.x > dirXMax) {
			wlkVel.y += (abs(wlkVel.y) - abs(dirYMax));
			wlkVel.x -= (wlkVel.x - dirXMax);
		}
	}
	if (travSouth && travWest) {
		if (wlkVel.y > dirYMax && wlkVel.x < dirXMax) {
			wlkVel.y -= (wlkVel.y - dirYMax);
			wlkVel.x += (abs(wlkVel.x) - abs(dirXMax));
		}
	}
	if (travNorth && travWest) {
		if (wlkVel.y < dirYMax && wlkVel.x < dirXMax) {
			wlkVel.y += (abs(wlkVel.y) - abs(dirYMax));
			wlkVel.x += (abs(wlkVel.x) - abs(dirXMax));
		}
	}
}
/*
void Player::limWalkVel() {
	// this number is simply used as a bench mark so we can check if the player is moving 
	//	a substantial amount diagonally.
	
	// check NE
	if (N && E) {
		wlkVel.x *= 0.70;
		wlkVel.y *= 0.70;
	}
	// check SE
	else if (S && E) {
		wlkVel.x *= 0.70;
		wlkVel.y *= 0.70;
	}
	// check NW
	else if (N && W) {
		wlkVel.x *= 0.70;
		wlkVel.y *= 0.70;
	}
	// check SW
	else if (S && W) {
		wlkVel.x *= 0.70;
		wlkVel.y *= 0.70;
	}

	if (S && wlkVel.y > maxWlkVel)
		wlkVel.y = maxWlkVel;
	if (N && wlkVel.y < -maxWlkVel)
		wlkVel.y = -maxWlkVel;
	if (E && wlkVel.x > maxWlkVel)
		wlkVel.x = maxWlkVel;
	if (W && wlkVel.x < -maxWlkVel)
		wlkVel.x = -maxWlkVel;
	
}
*/

//rudementary friction that doesnt even work
//?? Later take in friction from whatever surface the player is on
void Player::applyFriction()
{
	//sf::Vector2f rndVel(floor(finalVel.x / 1), floor(finalVel.y / 1));
	
	if (travEast)
		wlkVel.x -= wlkVel.x * kinFrictionCoef;
	if (travWest)
		wlkVel.x += -wlkVel.x * kinFrictionCoef;
	if (travSouth)
		wlkVel.y -= wlkVel.y * kinFrictionCoef;
	if (travNorth)
		wlkVel.y += -wlkVel.y * kinFrictionCoef;
	
	
}

void Player::updateDir()
{
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

// updates angle using Directions
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

// updates player's rotation to face the direction it is travelling
void Player::updateRot() {
	
	setRotation(movementAngle);
	
}

// updates the player's current tile
void Player::updatePlayerTile(TileMap* map) // update the curTile var for given map in index form
{
	curTile = sf::Vector2i(int(floor(getPosition().x / map->tileSize.x)), int(floor(getPosition().y / map->tileSize.y)));
}

// check for collision with collidable tiles in tilemap
// NOTE: ??maybelater I will take a level object and check for collision there?
void Player::collisionCheck(TileMap* map) {
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
		// top left corner only
		if (TL && !TR && !BL && !BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top));
			if ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top > (thisTile.getPosition().x + map->tileSize.x) - tempHitBox.left) {
				finalVel.x = finalVel.x + ((thisTile.getPosition().x + map->tileSize.x) - tempHitBox.left);
				wlkVel.x = 0;
			}
			else {
				finalVel.y = finalVel.y + ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top);
				wlkVel.y = 0;
			}
		}
		if (TR && !TL && !BL && !BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top));
			if ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top > (tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x) {
				finalVel.x = finalVel.x - ((tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x);
				wlkVel.x = 0;
			}
			else {
				finalVel.y = finalVel.y + ((thisTile.getPosition().y + map->tileSize.y) - tempHitBox.top);
				wlkVel.y = 0;
			}
		}
		if (BR && !TL && !BL && !TR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left + tempHitBox.width, tempHitBox.top + tempHitBox.height));
			if ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y > (tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x) {
				finalVel.x = finalVel.x - ((tempHitBox.left + tempHitBox.width) - thisTile.getPosition().x);
				wlkVel.x = 0;
			}
			else {
				finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y);
				wlkVel.y = 0;
			}
		}
		if (BL && !TL && !TR && !BR) {
			Tile thisTile = map->getTileWithPoints(sf::Vector2f(tempHitBox.left, tempHitBox.top + tempHitBox.height));
			if ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y > (thisTile.getPosition().x + map->tileSize.x) - tempHitBox.left) {
				finalVel.x = finalVel.x - (tempHitBox.left - (thisTile.getPosition().x + map->tileSize.x));
				wlkVel.x = 0;
			}
			else {
				finalVel.y = finalVel.y - ((tempHitBox.top + tempHitBox.height) - thisTile.getPosition().y);
				wlkVel.y = 0;
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
	return wlkVel;
}

sf::Vector2f Player::getFinalVel() {
	return finalVel;
}




