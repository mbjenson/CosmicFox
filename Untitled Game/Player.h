#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Sword.h"
#include <SFML/audio.hpp>

#include <math.h>

extern sf::Clock GLOBAL_GAME_CLOCK;

/*
* Player class
* 
* Contains all the code for the fox player in the game.
* The player is controlled by the user and navigated through each level.
*/
class Player : public Entity
{
public:

	Player(	sf::Texture& texture, sf::RenderWindow& win, 
			sf::Vector2u textureDim, int rowLength, 
			int rowNumber, float animationTime );
	
	
	// Player states
	enum class State {
		deactivated,
		nominal,
		dashing,
		cooldown,
		invulnerable,
		dead,
		attacking,
		attacked,
	};
	
	/*
	Updates the player.
	*/
	void update(float deltaTime, TileMap* map);

	// collision check functions 
	/*
	checks for collision with collidable tile in the logic grid.
	Resolves that collision using my own collision algorithm
	If a tile is labelled as 1
	*/
	void collisionCheckTile(TileMap* map);
	/*
	using a simple distance check, the player's bounding box is 
	checked against the enemy hitboxes that lie within a certain range.
	the player is pushed back by the enemies collision.
	*/
	void collisionCheckEnemy(sf::FloatRect hitBox, int damage);
	/*
	Checks if the player has fallen out of the map. checks the 
	4 corners of the player's foot hitbox to see if the player 
	is not on safe ground. switches the player into falling state
	if not safe.
	*/
	void collisionCheckVoid(TileMap* map);
	/*
	checks for new level tile logic. 
	*/
	int collisionCheckNewLevel(TileMap* map);
	
	// initializes player textures, animations, etc.
	void init();

	// set player state
	void setState(State _state);
	
	// respawn the player at a provided location
	void respawn(sf::Vector2f spawnPoint);

	// check player death
	void checkDeath(float dt);

	// sets hitbox rect in comparison to player given an offset and size
	void setHitBoxSize(sf::Vector2f size, sf::Vector2f offset);

	// various get functions mainly used for debugging
	sf::Vector2f getWlkVel();
	sf::Vector2f getFinalVel();
	sf::Vector2f getDashVel();
	sf::Vector2f getFacing();
	int getDashTimer();

private:

	void walkNorth();
	void walkEast();
	void walkSouth();
	void walkWest();

	// Animation functions set the current animation information
	// for the animation class.
	void wLeftAnim();
	void wRightAnim();
	void wUpAnim();
	void wDownAnim();
	void idleUpAnim();
	void idleDownAnim();
	void idleLeftAnim();
	void idleRightAnim();
	void dashAnimN();
	void dashAnimNE();
	void dashAnimE();
	void dashAnimSE();
	void dashAnimS();
	void dashAnimSW();
	void dashAnimW();
	void dashAnimNW();	

	
	/*
	*	the walking movement logic is as follows:
	*	The player inputs a direction on the keyboard,
	*	that is recognized by the game and the moveDir vector
	*   is set in response to the corresponding direction.
	*	For example: If I press 'W', the moveDir.y is set to -1.
	*	Then, the vector is normalized and walkVelocity is
	*   set to moveDir * walkSpeed * deltaTime.
	*/
	/*
	Normalized the walk velocity vector.
	*/
	void normalizeWalkVel();

	/*
	update the direction bools to match which the player is facing
	*/
	void setFacing();
	void setFacing(sf::Vector2f);

	/*
	Updates the players animation from information
	*/
	void setAnimation();

	/*
	update the direction bools the player is travelling.
	*/
	void updateTrav();

	/*
	update the location of the player's hitbox
	*/
	void updateHitBox();

	// Inherited draw fuction from the SFML library to which has been added several player-specific functions.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (!FLAG_DEAD) {
			if (voidCorners < 2)
				target.draw(shadowSprite);
			if (attacking) {
				target.draw(sword);
			}
		}
		target.draw(tSprite, states);
	}

	// cool function but not used anymore...
	void updateRotMouse();
	
public:
	// allowed movements
	bool northAllowed = true;
	bool eastAllowed = true;
	bool southAllowed = true;
	bool westAllowed = true;
	bool dashingAllowed = true;
	// current walking movements
	bool travNorth = false;
	bool travEast = false;
	bool travSouth = false;
	bool travWest = false;
	// current dashing movments
	bool isDashing = false;
	bool dashNorth = false;
	bool dashEast = false;
	bool dashWest = false;
	bool dashSouth = false;
	// button pressed bools
	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;
	bool spacePressed = false;
	bool LMBPressed = false;
	bool RMBPressed = false;

	bool attacking;
	bool beingHit;

	int hitBackTime;
	int invincibleTime;
	int flashRedTime;
	bool invincible;
	float knockBackSpeed;
	int voidCorners;

	sf::Vector2f hitVec;
	sf::Clock stunClock;
	sf::Vector2i curTile; // players current tile on specified tilemap

	sf::Vector2f hitBoxOffset;

	int maxHealth = 4;
	int curHealth;

	Sword sword;
	sf::Texture swordTex;
	sf::Texture shadowTex;
	sf::Sprite shadowSprite;

	sf::Clock deathTimer;
	int deathRestTime = 1500;

	sf::Vector2f fallPos;
	sf::Vector2f lastSafePos = sf::Vector2f(0, 0);

	// FLAGS:
	// the player is dead. This is set after any specific death sequences are finished.
	bool FLAG_DEAD;
	// lost all health and death animation needs to be done
	bool FLAG_NOLIFE;
	// fallen off the map
	bool FLAG_FALL;

	sf::Clock fallTimer;
	int fallTime = 800;
	float fallSpeed = 100.f;

	int score;

private:
	// information for each animation.
	// contains information used by the animation class to set
	// the animation
	sf::Vector2u wUpAnimDim;
	sf::Vector2u wDownAnimDim;
	sf::Vector2u wLeftAnimDim;
	sf::Vector2u wRightAnimDim;
	sf::Vector2u idleUpAnimDim;
	sf::Vector2u idleDownAnimDim;
	sf::Vector2u idleLeftAnimDim;
	sf::Vector2u idleRightAnimDim;

	sf::Vector2u dashAnimDimN;
	sf::Vector2u dashAnimDimNE;
	sf::Vector2u dashAnimDimE;
	sf::Vector2u dashAnimDimSE;
	sf::Vector2u dashAnimDimS;
	sf::Vector2u dashAnimDimSW;
	sf::Vector2u dashAnimDimW;
	sf::Vector2u dashAnimDimNW;

	sf::Vector2u deathAnimDim;
	
	float walkSpeed = 60.f;

	sf::Vector2f moveDir;
	sf::Vector2f walkVelocity;
	
	//dashing specs
	sf::Clock dashTimer;
	
	float dashSpeed = 140.f;
	int dashCooldown = 1400;

	bool falling;

	int dashSpeedTime = 285;
	
	int attackMoveSpeed = 35;

	sf::Vector2f dashVel = sf::Vector2f(0, 0);
	sf::Vector2f prepDashVel;

	sf::Vector2f lastFacing;

	sf::SoundBuffer attackBuffer;
	sf::SoundBuffer dashBuf;
	sf::Sound s1;
	sf::Sound s2;
	
	sf::Vector2f finalVel;
	sf::Vector2f hitBoxSize;
	State state;
	sf::FloatRect healthHitBox = sf::FloatRect(0, 0, 8, 13);

	float playerAngle;

	sf::RenderWindow* pWindow;
};