
#include <SFML/graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <math.h>
#include <iostream>
//#include <thread>

#include "PauseButton.h"
#include "deathScreen.h"
#include "Menu.h"
#include "Player.h"
#include "Camera.h"
#include "ResHandler.h"
#include "GrassLandsLevel.h"
#include "HudBar.h"
#include "DashMeter.h"
#include "Spirit.h"
#include "IntroLevel.h"

using namespace std;

bool DEBUG;
sf::Clock GLOBAL_GAME_CLOCK;

// implement a state system.
//		1) game state will allow the user to play the game, pause the game, and show a blurred out version of visible screen in pause menu
//		2) a main menu state that will allow the user to change the music volume, and adjust other things

// 

/*
* NOTES:
* 
* ->	Make sure dash only check for collision with walls. So that you can dash past enemies and dash over gaps in ground.
* 
* ->	Blind jump uses a system where tiles of different types inherit from the tile class and have different attributes
*		it then check to see if a tile is grass and the tile below it is empty space, if it is the space below it is
*		is filled with an 'edge' tile that makes the tile look 3d. this is good for random map generation and also good
*		for regular planned generation.
* 
* ->	? note sure if do ? Implement a way that tiles can have animations with tilemapmk2. cant use the current animation class
* 
* ->	keep track of the last safe tile the player was standing on so that if they fall, if their health
*		is sufficient, they are respawned back on the last safe tile.
* 
*  -> SPACE FOX!;
*  -> COSMIC FOX!;
*/

//  TODO:
//  animate the player's shadow and update it. if have time
//	NOTE: use the same animation functions that are currently used for the player animations
//  NOTE: also use the animation dimensions.

// MAP IDEA:
// bigg pillars walk between, royal city things. flat maps with holes. epic royal ocean/empirical tilemap. white marbel.
// two big pillars the player walks between with trees and whatnot.

// TODO:


//CURRENT:

// have player start in small grassy area with crashed (or just landed) rocket, here he will enter into the cave, in cave he will enter out into main area...

// change music thing: for gameAmbience (currently used as main menu music), remove one of the first repetitions of first bar; it is very boring.

// work on collision Check new level in player.cpp

// experiment with stack allocating the textures if it gets too slow

// create a way that sounds can be present in the game, like walking sounds, dashing, dying, sword slash, etc

// give levels the option to provide a shader to the player for player to be draw with

// make it so enemies push each other apart

// allow travel between levels. this will involve freeing memory used by previous level. Each level can be heap allocated.
// when the game is started, a linked list, each containing NULL level pointers will be created.
// Once travel to a new level has been initiated, the player will despawn from current level and delete will be called on previous level.
// **NOTE: we use delete because I am using 'new' keyword and delete() is faster than free().

// wont need enemy collisionCheckVoid because we will simply check if tilemap logic is 1 || 2. then the enemy wont fall off ledge even if
// its a void there. Its just numbers. how each class interperetes the information is up to them.

// enemy has bool which controls whether or not the enemies are allowed to chase the player. this can be toggled for events like if the player
//	falls or is dead. (check to make sure that when the player falls, the hitbox does not also fall with it. 

//fix, the grass edge tiles, they are deceiving and make it look like the player can go out farther
//		than it can

// implement a pathfinding algorithm for the enemy that can run on a thread and doesn't need to finish
// for the game loop to be completed. this algorithm will allow the enemy to not simply fall off of the ledge
//	if the player is on other side of gap

// finish player death anim.
// workout player falling function:
	// when fall, player must be drawn behind certain things that it would usually be drawn in front of.
	// a possible solution to this is, when the player falls, redraw the map in such a way that the player
	// is drawn at the end of it's row but for the static tileMap. This would work and I wouldn't have to manage a lot of crap.

// add player death and new draw enemy sprite
// add a pointer to a vector of enemies into the level file



// remove mapping functions.h from this project more function calls than necessary is inefficient and should be done inline if possible.

// a player will have a vector of item pointers. So only need to load in one item and if player has it, 
//		it just points to original

//  Entity shadows... not possible

//  enemies:
//		In the level class, have a component that handles all the enemies in the game for updating.
//		check for enemy hit by looping through vector of enemies and getting their positions and checking
//		if the distance between the enemy and the player is below a threshhold, then check for collisions.

// Sword combo:
//		add to sword class a function that will allow for 3 different hboxes maybe.
//		make it so that when you use the sword, you are slowed and move forward slightly
//		make the sword combo 3 things long.

// LightMap... not for this project
// implement a light map system that is used when rendering the screen. Draw a black rectanlge over the whole screen and apply a shader to it
//	that cooperates with the light map.
// Implement lighting for different objects. Check out Saved web article by Matt Greer: https://mattgreer.dev/blog/dynamic-lighting-and-shadows/

void deathTransition(sf::RenderWindow* win) {
	sf::Clock timer;
	sf::Texture winTex;
	winTex.create(win->getSize().x, win->getSize().y);
	sf::Sprite mask(winTex);
	mask.setColor(sf::Color(255, 255, 255, 100));
	sf::BlendMode none;
	while (timer.getElapsedTime().asMilliseconds() < 1000) {

		//mask.setColor(sf::Color(255, 255, 255, timer.getElapsedTime().asMilliseconds() / 5));
		win->clear();
		win->draw(mask);
		win->display();
	}
}
// fade to black then back
void levelTransition(sf::RenderWindow* win) {
	sf::Clock timer;
	sf::Texture winTex;
	winTex.create(win->getSize().x, win->getSize().y);
	sf::Sprite mask(winTex);
	//sf::BlendMode none;

	while (timer.getElapsedTime().asMilliseconds() < 1000) {
		win->clear();
		win->draw(mask);
		win->display();
	}

}

void setKeyPressesKBD(Player& player) {
	player.upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	player.downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	player.leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	player.rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	player.spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	player.LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	player.RMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

// takes a float and the desired places and returns a string version of the float rounded to numPlaces
string roundedString(int numPlaces, float x) {
	int places = pow(10, numPlaces);
	int wholeNum = int((x * 100 + 0.5) / 100);
	int decPlaces = int((x - wholeNum) * places);
	string rounded = to_string(wholeNum) + "." + to_string(decPlaces);
	return rounded;
}

// event loop in a function to make the main function cleaner
void processEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::LostFocus)
			window.setFramerateLimit(5);
		if (event.type == sf::Event::GainedFocus)
			window.setFramerateLimit(0);
		if (event.type == sf::Event::KeyReleased){
			if (event.key.code == sf::Keyboard::G) {
				DEBUG ^= true;
			}
		}
	}
}

int main() {

	enum class State {
		game,
		menu,
		death,
	};
	State state = State::menu;

	sf::Vector2f winDim(2560, 1440);
	//sf::Vector2f winDim(1920, 1080);
	sf::RenderWindow window(sf::VideoMode(winDim.x, winDim.y), "Untitled Game", sf::Style::Close | sf::Style::Fullscreen);
	
	sf::View menuView;
	menuView.setCenter(951, 540);
	menuView.setSize(1920, 1080);

	Camera camera;
	camera.setSize(sf::Vector2f(1920, 1080));
	camera.zoom(0.15f);
	//camera.zoom(0.70f);

	sf::Font roboto;
	if (!roboto.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {
		return -1;
	}
	sf::Text winText;
	winText.setFont(roboto);
	winText.setCharacterSize(10);
	winText.setScale(0.5, 0.5);
	winText.setFillColor(sf::Color::White);

	sf::Texture fox;
	if (!fox.loadFromFile("Textures/foxSpriteSheetmk2.png"))
		return -1;
	
	sf::Texture vignette;
	if (!vignette.loadFromFile("Textures/vignetteShadow.png"))
		return -1;

	sf::Sprite vig(vignette);
	vig.setScale(0.8, 0.5);

	Player p1(fox, window, sf::Vector2u(16, 16), 8, 0, 80.f);
	p1.setPosition(sf::Vector2f(400.f, 100.f));
	p1.init();
	p1.setState(Player::State::nominal);
	camera.setCenter(p1.getPosition());

	sf::Texture heart;
	if (!heart.loadFromFile("Textures/heart.png")) {
		return -1;
	}

	HudBar lifeCount(heart, sf::Vector2f(5, 5), p1.maxHealth, sf::Vector2u(9, 9));
	
	DashMeter dashmeter;

	sf::Texture spriritT;
	if (!spriritT.loadFromFile("Textures/spirit.png"))
		return -1;
	
	Spirit spirit(spriritT, sf::Vector2u(7, 8), 5, 0, 60.f);
	spirit.init();

	deathScreen deathMenu;
	
	//levelVec
	vector<Level*> levelVec(2);
	int curLevelIndex = 1;
	
	levelVec.at(1) = new GrassLandsLevel(&p1);
	//levelVec.at(0) = new IntroLevel(&p1);

	Level* curLevel;
	curLevel = levelVec.at(curLevelIndex);
	p1.setPosition(curLevel->playerSpawn);
	
	sf::Music music;
	if (!music.openFromFile("Sounds/gameAmbience1.wav"))
		return -1;
	music.play();
	music.setVolume(65.f);
	music.setLoop(true);

	sf::BlendMode none;

	Menu mainMenu;
	mainMenu.init();

	PauseButton pauseB;
	pauseB.init();
	
	sf::Texture win;
	win.loadFromFile("Textures/win.png");
	sf::Sprite winScreen(win);
	
	winScreen.setScale(3.f, 3.f);
	int endgame = 0;

	sf::Clock mainClock;
	sf::Clock dtClock;
	while (window.isOpen())
	{
		float dt = dtClock.restart().asSeconds();
		processEvents(window);
		// Game.GameState ** change to this later using Game.hpp
		if (state == State::menu) {
			window.setView(menuView);
			window.clear();
			int result = mainMenu.update(window);
			if (result == 1) {
				state = State::game;
			}
			if (result == 2) {
				// quit game.
				
				window.close();
			}
			window.display();
		}
		if (state == State::death) {
			window.setView(menuView);
			window.clear();
			deathMenu.init();
			int result = deathMenu.update(window);
			if (result == 1) {
				p1.respawn(curLevel->playerSpawn);
				p1.curHealth = p1.maxHealth;
				state = State::game;
			}
			if (result == 2) {
				window.close();
			}
			window.display();
		}
		if (state == State::game) {
			
			// update bg position
			//newLevel.tileMap->updateBG(camera.getCenter());
			curLevel->tileMap->updateBG(camera.getCenter());
			setKeyPressesKBD(p1);
			window.clear();

			sf::Vector2f tempVec(p1.getPosition().x, p1.getPosition().y - 100.f);
			if (curLevel->usingShader)
				curLevel->shader.setUniform("circleCenter", sf::Vector2f(window.mapCoordsToPixel(tempVec)));
			// using renderState (blend mode) we can blend the background texture with the foreground texture
			window.draw(curLevel->tileMap->bg, sf::RenderStates(none));
			p1.update(dt, curLevel->tileMap);
			camera.update(p1, dt, 
				sf::Vector2f(	curLevel->tileMap->getMapDimTiles().x * curLevel->tileMap->tileSize, 
								curLevel->tileMap->getMapDimTiles().y * curLevel->tileMap->tileSize));
			window.setView(camera);
			
			curLevel->updateEnemies(dt, &window);
			curLevel->render(window);
			
			spirit.update(p1.getPosition(), dt);
			window.draw(spirit);

			// VIGNETTE EFFECT:
			vig.setPosition(sf::Vector2f(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().y - camera.getSize().y / 2));
			window.draw(vig);
			
			// HUD:
			lifeCount.render(window, p1.curHealth, sf::Vector2f(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().y - camera.getSize().y / 2));
			dashmeter.render(window, p1.getDashTimer(), sf::Vector2f(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().y - camera.getSize().y / 2));

			int pause = pauseB.update(window);
			if (pause) {
				state = State::menu;
			}
			// handling inter-level travel
			int levelInstruction = p1.collisionCheckNewLevel(curLevel->tileMap);
			if (levelInstruction == 2) {
				delete(levelVec.at(curLevelIndex));
				curLevelIndex += 1;
				if (curLevelIndex == 1) {
					levelVec.at(curLevelIndex) = new GrassLandsLevel(&p1);
				}
				curLevel = levelVec.at(curLevelIndex);
				p1.setPosition(curLevel->playerSpawn);
				levelTransition(&window);
			}
			/*
			if (levelInstruction == 1) {
				curLevelIndex -= 1;
				if (curLevelIndex < 0) {
					curLevelIndex = 0;
				}
				curLevel = levelVec.at(curLevelIndex);
			}
			*/
			if (p1.FLAG_DEAD) {
				if (p1.deathTimer.getElapsedTime().asMilliseconds() > p1.deathRestTime) {
					state = State::death;
				}
			}
			if (curLevelIndex == 1 && levelVec.at(curLevelIndex)->eVec.empty()) {
				if (endgame < 2000) {
					winScreen.setPosition(camera.getCenter().x - camera.getSize().x / 4, camera.getCenter().y - camera.getSize().y / 2);
					window.draw(winScreen);
					endgame++;
				}
			}
			
			if (DEBUG) {

				string xPlayerCord = roundedString(2, p1.getPosition().x);
				string yPlayerCord = roundedString(2, p1.getPosition().y);

				winText.setPosition(sf::Vector2f(camera.getCenter().x + 5 - camera.getSize().x / 2, camera.getCenter().y + 5 - camera.getSize().y / 2));
				winText.setString("x = " + xPlayerCord);
				window.draw(winText);

				winText.setString("\ny = " + yPlayerCord);
				window.draw(winText);

				winText.setString("\n\nxVel = " + roundedString(3, p1.getFinalVel().x) + "\nyVel = " + roundedString(3, p1.getFinalVel().y));
				window.draw(winText);

				winText.setString("\n\n\n\nDashTimer: " + to_string(p1.getDashTimer()));
				window.draw(winText);

				winText.setString("\n\n\n\n\nDashVelx = " + roundedString(3, p1.getDashVel().x) +
					"\nDashVely = " + roundedString(3, p1.getDashVel().y));
				window.draw(winText);

				winText.setString("\n\n\n\n\n\n\nFacingx = " + to_string(p1.getFacing().x) +
					"\nFacingy = " + to_string(p1.getFacing().y));
				window.draw(winText);

				winText.setString("\n\n\n\n\n\n\n\n\nGlobal Game Clock = " + to_string(GLOBAL_GAME_CLOCK.getElapsedTime().asMilliseconds()));
				window.draw(winText);

				winText.setString("\n\n\n\n\n\n\n\n\n\ndeltaTime = " + to_string(dt));
				window.draw(winText);
			}

			window.display();
		}
	}
	return 0;
}