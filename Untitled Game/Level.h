#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "ResHandler.h"

/*
	Generic level class that can be provided with player*. contains the tileMap and necessary things for a specific level
*/
class Level 
{
public:


	void render(sf::RenderWindow& win);
	//int init(); declare an innit function for each Version of the level that inits all components of the Level
	
	// vector of enemies for a given level;
	// player can check for hit on all of the enemies by checking which ones are within range of each other, if
	TileMap* tileMap;
	// interactable map from TileMap;
	Player* player; // get needed infomation about player status for tileMap
	
	// enemy map stuff
	// sound map stuff
};

