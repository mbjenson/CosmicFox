#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Camera.h"
#include "ResHandler.h"
#include "Level.h"

// in a way I take most of the crap from main.cpp and have it happen here.

class Game {
public:
	enum class GameState {
		mainMenu,
		loading,
		play,
		pause,
		saving,
	};

private:

	sf::RenderWindow GAME_WINDOW;
	Camera camera;

};
