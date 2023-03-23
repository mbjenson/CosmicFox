#pragma once
#include "Entity.h"
#include "TileMap.h"
#include <math.h>

class Player : public Entity
{
public:

	Player(	sf::Texture& texture, sf::RenderWindow& win, 
			sf::Vector2u textureDim, int rowLength, 
			int rowNumber, float animationTime );

	void walkNorth(float deltaTime);
	void walkEast(float deltaTime);
	void walkSouth(float deltaTime);
	void walkWest(float deltaTime);

	void dash(float curTime, float deltaTime);

	void updateMovement(float deltaTime, TileMap* map);

	void update(float deltaTime, TileMap* map);

	// allowed movements
	bool northAllowed = true;
	bool eastAllowed = true;
	bool southAllowed = true;
	bool westAllowed = true;
	bool dashingAllowed = true;

	bool travNorth;
	bool travEast;
	bool travSouth;
	bool travWest;
	bool dashNorth;
	bool dashEast;
	bool dashWest;
	bool dashSouth;

	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;
	bool escapePressed;

	//later put some update functions into a more concise and clear single public function
	sf::Vector2i curTile;
	void updatePlayerTile(TileMap* map); // update the curTile var for given map
	
	void collisionCheck(TileMap* map);
	
	bool isDashing = false;
	//void checkDash(int frameNum, float deltaTime);

	//the actual direciton that player is travelling
	

	sf::Vector2f getWlkVel();
	sf::Vector2f getFinalVel();
	
	// create a switch statement in player.cpp that checks if the player is in one of these states and if so, 
	// sets parameters for them which change how the player is playing
	enum class State {
		deactivated,
		nominal,
		dashing,
		cooldown,
		invulnerable,
		dead
	};

	void init();
	void getKeyPresses(bool up, bool down, bool left, bool right, bool space, bool escape);
	void setState(State _state);

private:
	
	//add animations functions that change the row based on instructions
	//animation information
	void wLeftAnim();
	void wRightAnim();
	void wUpAnim();
	void wDownAnim();
	void idleUpAnim();
	void idleDownAnim();
	void idleLeftAnim();
	void idleRightAnim();

	// the animations should all have the same runtime but different row number
	// ** update these in a player.init() function that just sets these values
	sf::Vector2u wUpAnimDim;
	sf::Vector2u wDownAnimDim;
	sf::Vector2u wLeftAnimDim;
	sf::Vector2u wRightAnimDim;
	sf::Vector2u idleUpAnimDim;
	sf::Vector2u idleDownAnimDim;
	sf::Vector2u idleLeftAnimDim;
	sf::Vector2u idleRightAnimDim;

	//effects
	// here I will code in functions that do things to the players sprite and change how it works
	// like adding a flashing red effect for low health
	// or like a flashing for invulnerability
	
	//walking specs
	float maxWlkVel = 0.07;
	float wlkAcc = 1.f;
	
	//dashing specs
	float maxDashVel = 0.14;
	float dashAcc = 5.f;
	int dashTimeStart = 0;
	int dashCooldown = 3;
	//int dashLength = 60;
	//void updateDash(float deltaTime, int frameNum);
	// make a variable to represent the current change in velocity (dy/dx)
	sf::Vector2f deltaVel;
	

	sf::Vector2f finalVel;
	sf::Vector2f dashVel;
	void limitDashVel();
	sf::Vector2f wlkVel;
	void limWalkVel();
	//sf::Vector2f limitVel(float deltaTime, float maxVel, sf::Vector2f velocity);

	//applying friction
	float kinFrictionCoef = 0.01;
	void applyFriction();

	//direction of movement
	float movementAngle = 0;
	float lastMovementAngle = 0;
	void updateMovementAngle();
	
	void updateDir();
	//rotating the player towards the mouse
	void updateRot();
	void updateRotMouse();

	sf::RenderWindow* pWindow;
	sf::Vector2f hitBoxSize = sf::Vector2f(10, 10);

	void updateHitBox();

	State state;
	
	
};

