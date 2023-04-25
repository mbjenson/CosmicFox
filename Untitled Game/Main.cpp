
#include <SFML/graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <math.h>
#include <iostream>
//#include <thread>

#include "PauseButton.h"
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
// this is temp main function for when I want to test other things 



/*
int main() {
	sf::Vector2f winDim(1920, 1080);

	sf::RenderWindow window(sf::VideoMode(winDim.x, winDim.y), "Untitled Game", sf::Style::Close | sf::Style::Resize);

	
	//sf::Texture black;
	//if (!black.loadFromFile("Textures/black.png")) {
	//	return -1;
	//}
	//sf::Sprite box(black);
	
	sf::Texture bgT;
	if (!bgT.loadFromFile("Textures/earth.png"))
		return -1;
	sf::Sprite bg(bgT);
	
	
	
	sf::Texture tex;
	tex.create(winDim.x, winDim.x);
	sf::Sprite spr(tex);
	
	sf::Vector2f topLeft(0, 0);
	sf::Vector2f playerPos(400.f, 200.f);
		//distance from top left of screen
	

	sf::Shader shader;
	if (!shader.loadFromFile("Shaders/test6.frag", sf::Shader::Fragment))
		return -1;
	
	shader.setUniform("u_resolution", sf::Vector2f(tex.getSize().x, tex.getSize().y));
	shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
	sf::Clock mainClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed())
				window.close();
		}
		sf::Vector2f center(topLeft.x + sf::Mouse::getPosition().x + 250, topLeft.y + sf::Mouse::getPosition().y + 400);
		shader.setUniform("circleCenter", sf::Vector2f(center));

		window.clear();
		
		window.draw(bg);
		window.draw(spr, &shader);
		

		window.display();
	}
}
*/



int main() {

	bool gameState = false;
	bool menuState = true;
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

	
	//GrassLandsLevel newLevel;
	//int hey = sizeof(newLevel);
	//newLevel.init(&p1);
	
	//IntroLevel introL;
	//int hey1 = sizeof(introL);
	//introL.init(&p1);
	
	//IntroLevel* level1;
	//GrassLandsLevel* level2;


	//levelVec
	vector<Level*> levelVec(2);
	int curLevelIndex = 1;

	//levelVec.at(0) = new IntroLevel(&p1);
	levelVec.at(1) = new GrassLandsLevel(&p1);
	
	Level* curLevel;
	curLevel = levelVec.at(curLevelIndex);

	// check every frame if checkNewLevel is 0 then do nothing, if is 1 then go to previous level, if is 2 then set curlevel = to the next level
	
	// everyframe, check for collision with new level logic blocks in tilemap logic grid. 

	//p1.setPosition(sf::Vector2f(25.f, 25.f));
	//sf::Music music;
	//if (!music.openFromFile("Sounds/gameAmbience1.wav"))
	//	return -1;
	//music.play();
	//music.setVolume(50.f);


	sf::BlendMode none;

	Menu mainMenu;
	mainMenu.init();

	PauseButton pauseB;
	pauseB.init();
	

	sf::Clock mainClock;
	sf::Clock dtClock;
	while (window.isOpen())
	{
		float dt = dtClock.restart().asSeconds();
		processEvents(window);
		// Game.GameState ** change to this later using Game.hpp
		if (menuState) {
			window.setView(menuView);
			window.clear();
			int result = mainMenu.update(window);
			if (result == 1) {
				gameState = true;
				menuState = false;
			}
			if (result == 2) {
				// quit game.
				
				window.close();
			}
			window.display();
		}
		if (gameState) {
			
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
				gameState = false;
				menuState = true;
			}
			/*
			tileMap->texDim1 = sf::IntRect(1, 1, 25, 40);
			tileMap->texDim2 = sf::IntRect(26, 1, 25, 40);
			tileMap->texDim3 = sf::IntRect(54, 0, 21, 33);
			*/
			/*
			tileMap->texDim1 = sf::IntRect(0, 0, 13, 19);
			tileMap->texDim2 = sf::IntRect(16, 0, 16, 32);
			tileMap->texDim3 = sf::IntRect(34, 1, 35, 28);
			*/
			// handling inter-level travel
			int levelInstruction = p1.collisionCheckNewLevel(curLevel->tileMap);
			
			if (levelInstruction == 2) {
				delete(levelVec.at(curLevelIndex));
				curLevelIndex += 1;
				if (curLevelIndex == 1)
					levelVec.at(curLevelIndex) = new GrassLandsLevel(&p1);
				curLevel = levelVec.at(curLevelIndex);
			}
			if (levelInstruction == 1) {
				curLevelIndex -= 1;
				if (curLevelIndex < 0) {
					curLevelIndex = 0;
				}
				curLevel = levelVec.at(curLevelIndex);
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




/*
	sf::Texture enemyT;
	if (!enemyT.loadFromFile("Textures/playerCube16.png"))
		return -1;

	Enemy* e1 = new Enemy(&enemyT, sf::Vector2f(16, 16));
	//e1.setOrigin(sf::Vector2f(enemyT.getSize().x / 2, enemyT.getSize().y / 2));
	e1->init();
	e1->setPosition(45.f, 45.f);

	Enemy* e2 = new Enemy(&enemyT, sf::Vector2f(16, 16));
	e2->init();
	e2->setPosition(45.f, 80.f);

	std::vector<Enemy> eVec;
	eVec.push_back(*e1);
	eVec.push_back(*e2);

	//std::vector<Enemy> delQueue;
	*/

// TODO:
// ?? maybe not needed because I am going to have a 16x16 sprite anyway
// add new check for the tile collision that checks the center of each component of hitbox on the x and the y
/*f
//1)
p1.updatePlayerTile(&tileMap);
camera.update(p1, dt);
window.setView(camera);
//2)
sf::Vector2i renderSize(13, 8);
tileMap.render(p1.curTile, window, renderSize);
//p1.updateAnimation(&pMoveClock);
//3)
p1.updateMovement(dt, &tileMap);
//sh1.setUniform("time", mainClock.getElapsedTime().asSeconds());
window.draw(p1);
// top tile map is rendered last because of draw order
topTileMap.render(p1.curTile, window, renderSize);
*/

/*
	int tileTypes[] = {
		0, 0, 1, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 0, 1, 0,
		1, 0, 0, 0, 1, 1, 0, 1,
		0, 0, 0, 6, 6, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 6, 6, 0, 0, 0,
		1, 1, 1, 2, 3, 0, 0, 0,
		6, 6, 6, 6, 6, 6, 6, 6,
	};
	int logGrid[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,	};

	sf::Vector2u groundTexSize(16, 16);
	Tile grass(terrarin, groundTexSize, 0);
	Tile grassStone(terrarin, groundTexSize, 1);
	Tile stoneWall(terrarin, groundTexSize, 2);
	Tile stone(terrarin, groundTexSize, 3);
	Tile stairsR(terrarin, groundTexSize, 4);
	Tile stairsL(terrarin, groundTexSize, 5);
	Tile under(terrarin, groundTexSize, 6);

	Tile tiles1[] = { grass, grassStone, stoneWall, stone, stairsR, stairsL, under };

	sf::Vector2u temp_tileSize(16, 16);
	TileMap tileMap(7, tiles1, temp_mapSize, tileTypes, logGrid, temp_tileSize);
	*/


/*
	// Shader settup
	if (!sf::Shader::isAvailable())
		return -1;

	sf::Shader sh1;
	if (!sh1.loadFromFile("Shaders/light_test.frag", sf::Shader::Fragment))
		return -1;
	sh1.setUniform("u_resolution", sf::Vector2f(winDim.x, winDim.y));

	sf::Texture blackT;
	if (!blackT.loadFromFile("Textures/black.png"))
		return -1;
	sf::Sprite lightS(blackT);

	lightS.setScale(
		winDim.x / lightS.getGlobalBounds().width,
		winDim.y / lightS.getGlobalBounds().height
	);
	*/



	/*
		sf::Texture heart;
		if (!heart.loadFromFile("Textures/heart.png"))
			return -1;

		sf::Sprite test(heart);

		sf::RenderTexture bgTex;
		bgTex.create(winDim.x, winDim.y);
		bgTex.draw(test);
		bgTex.display();
		sf::Sprite bg(bgTex.getTexture());

		HudBar lifeBar(heart, sf::Vector2f(5, 5), &camera);
		*/


		//lifeBar.render(window, p1.health);

					//bg.setPosition(p1.getPosition().x-19, p1.getPosition().y-19);
					//window.draw(bg);

//if (newMap->checkForUpdate(p1.getPosition())) {
			//	newMap->updateTexMap();
			//	newMap->updatePlayerChunk(p1.getPosition());
			//}
			//sf::Sprite mapSprite(newMap->getMapTex()->getTexture());

			//window.draw(mapSprite);
			//shadowSprite.setPosition(sf::Vector2f(p1.getPosition().x - 8, p1.getPosition().y - 6));
			//window.draw(shadowSprite);
			//window.draw(p1);