#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Sword.h"

#include <math.h>

extern sf::Clock GLOBAL_GAME_CLOCK;

class Player : public Entity
{
public:

	Player(	sf::Texture& texture, sf::RenderWindow& win, 
			sf::Vector2u textureDim, int rowLength, 
			int rowNumber, float animationTime );
	
	// try and declare most things inside of the class so that you dont need to pass all above giberish as params
	//Player (sf::RenderWindow& win, sf::Vector2u textureDim)
	void walkNorth();
	void walkEast();
	void walkSouth();
	void walkWest();
	//main update function for the player
	//void update(float deltaTime, TileMap* map);
	void update(float deltaTime, TileMap* map);
	// allowed movements
	bool northAllowed = true;
	bool eastAllowed = true;
	bool southAllowed = true;
	bool westAllowed = true;
	bool dashingAllowed = true;
	// current walking movements
	bool travNorth;
	bool travEast;
	bool travSouth;
	bool travWest;
	// current dashing movments
	bool isDashing;
	bool dashNorth;
	bool dashEast;
	bool dashWest;
	bool dashSouth;
	// button pressed bools
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;
	bool LMBPressed;
	bool RMBPressed;
	//attacking
	bool attacking;
	//attacked
	bool beingHit;
	sf::Clock stunClock;
	int hitBackTime;
	int invincibleTime;
	int flashRedTime;
	bool invincible;
	sf::Vector2f hitVec;
	float knockBackSpeed;

	//void updatePlayerTile(TileMap* map); // update the curTile var for given map
	// check for collision with a specified tilemap
	//void collisionCheckTile(TileMap* map);
	void collisionCheckTile(TileMap* map);
	void collisionCheckEnemy(sf::FloatRect hitBox, int damage);
	void collisionCheckVoid(TileMap* map);
	int collisionCheckNewLevel(TileMap* map);
	int voidCorners;
	// players current tile on specified tilemap
	sf::Vector2i curTile;
	
	// player states
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
	// inits many values for the player like textures, animations, bools, and other things
	void init();
	//void getKeyPresses(bool up, bool down, bool left, bool right, bool space, bool escape);
	void setState(State _state);
	int getDashTimer();
	sf::Vector2f getWlkVel();
	sf::Vector2f getFinalVel();
	sf::Vector2f getDashVel();
	sf::Vector2f getFacing();
	sf::Vector2f hitBoxOffset;

	void setHitBoxSize(sf::Vector2f size, sf::Vector2f offset);

	void updatePWindow(sf::RenderWindow& win);

	int maxHealth = 4;
	int curHealth;

	Sword sword;
	sf::Texture swordTex;
	sf::Texture shadowTex;
	sf::Sprite shadowSprite;
	
	sf::Clock deathTimer;
	int deathRestTime = 1500;

	bool detectHit(sf::FloatRect badBox);

	void fall(); // when fall, player must be drawn behind certain things that it would usually be drawn in front of.
				// a possible solution to this is, when the player falls, redraw the map in such a way that the player
				// is drawn at the end of it's row but for the static tileMap. This would work and I wouldn't have to manage a lot of crap.

	void checkDeath(float dt);
	sf::Clock fallTimer;
	int fallTime = 800;
	float fallSpeed = 100.f;
	sf::Vector2f fallPos;
	sf::Vector2f lastSafePos;
	void respawn(sf::Vector2f spawnPoint);
	// FLAGS:
	// the player is dead. switch to true for both falling and killed
	bool FLAG_DEAD;
	// the player has just lost all health and death anim needs to be done
	bool FLAG_NOLIFE;
	bool FLAG_FALL;
	// other flags
	//bool FLAG_NEWLEVEL;



private:


	//animation functions that set the row number for the animation for the player
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

	void invincibleEffect();
	// ** update these in a player.init() function that just sets these values
	// the animations should all have the same runtime but different row number
	// animation dimensions (which row on spriteSheet and how long each row is).
	//Animation walkUpAnim = Animation()
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

	/*
	* Effects #include effects.hpp
	* here I will code in functions that do things to the players sprite and change how it works
	* like adding a flashing red effect for low health
	* or like a flashing for invulnerability
	*/
	
	/*
	*	the walking movement logic is as follows:
	*	The player inputs a direction on the keyboard,
	*	that is recognized by the game and the moveDir is set
	*	in response. 
	*	For example: If I press 'W', the moveDir.y is set to -1.
	*	Then, the vector is normalized and walkVelocity is 
	*   set to moveDir * walkSpeed * deltaTime.
	*/
	
	// \/ yes
	//float walkSpeed = 80.0f;
	float walkSpeed = 60.f;
	//float walkSpeed = 200.f;
	//float walkSpeed = 75.0f;

	void normalizeWalkVel();
	sf::Vector2f moveDir;
	sf::Vector2f walkVelocity;
	
	//dashing specs
	sf::Clock dashTimer;
	//1)float dashSpeed = 275.f;
	//2) float dashSpeed = 180.f;
	//3) float dashSpeed = 220.f
	float dashSpeed = 170.f;
	//1) int dashCooldown = 1000;
	int dashCooldown = 1400;

	bool falling;
	//1)int dashSpeedTime = 250;
	//int dashSpeedTime = 200;
	int dashSpeedTime = 250;
	//int dashSpeedTime = 165;
	sf::Vector2f dashVel;
	sf::Vector2f prepDashVel;

	
	void setAnimation();
	sf::Vector2f lastFacing;
	void setFacing();
	void setFacing(sf::Vector2f);

	
	int attackMoveSpeed = 35;
	//sf::Clock attackTimer;


	// ** may not need this
	// simply checks if the player is travelling diagonally and sets the bool accordingly.
	void setDiagBool();
	bool travDiag;
	// sum of dash velocity and walk velocity.
	sf::Vector2f finalVel;
	
	// applies friction to the players walkspeed
	void applyWalkFriction();
	float kinFrictionCoef = 0.018;

	//direction of movement (**old)
	//float movementAngle = 0;
	//float lastMovementAngle = 0;
	
	// ** probably dont need but keeping in case
	// updates playerAngle based on directon
	//void updateDir();
	// updates directional booleans to match which direction the player is travelling in
	void updateTrav();
	// ** may not use but I will be setting the sword swinging direction to face the mouse so keeping it for that reason.
	// rotating the player towards the mouse
	
	void updateRotMouse();
	// player hitbox size
	sf::Vector2f hitBoxSize; // = sf::Vector2f(10, 10);
	// updates the location of the hitbox with the players current location
	void updateHitBox();

	State state;

	sf::FloatRect healthHitBox;
	void updateHealthHitBox();

	float playerAngle;
	// used to get information from the window the player is being drawn on
	sf::RenderWindow* pWindow;
	
	

	//this is here so that I can draw specific things for the player like sword or shadow or effects and whatnot
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

		//sf::RectangleShape lastSafe(sf::Vector2f(3.f, 3.f));
		//lastSafe.setPosition(lastSafePos);
		//lastSafe.setFillColor(sf::Color::Red);
		//target.draw(lastSafe);

		//sf::RectangleShape hitBoxdraw(sf::Vector2f(8.f, 6.f));
		//hitBoxdraw.setFillColor(sf::Color::Red);
		//hitBoxdraw.setPosition(sf::Vector2f(hitBox.left, hitBox.top));
		//target.draw(hitBoxdraw);
		
		//sf::RectangleShape rect(sf::Vector2f(8, 13));
		//rect.setPosition(sf::Vector2f(getPosition().x - 4, getPosition().y - 5));
		//target.draw(rect);

		target.draw(tSprite, states);
	}
};

//void updateRot();
//void updateMovementAngle();
//void updateMovement(float deltaTime, TileMap* map);