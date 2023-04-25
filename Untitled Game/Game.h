#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Camera.h"
#include "ResHandler.h"
#include "Level.h"


// in a way I take most of the crap from main.cpp and have it happen here.

class Game {
public:
	bool MAINMENU;
	
	int loadNewLevel();

private:

	sf::RenderWindow GAME_WINDOW;
	Camera camera;
	sf::View mainMenuView;


};
