#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"
#include "ResHandler.h"

/*
	Generic level class that can be provided with player*. contains the tileMap and necessary things for a specific level
*/
class Level 
{
public:

	void render(sf::RenderWindow& win);
	//int init(); declare an innit function for each Version of the level that inits all components of the Level
	
	TileMap* tileMap;
	// interactable map from TileMap;
	Player* player; // get needed infomation about player status for tileMap
	
	// enemy map stuff
	// sound map stuff
};

