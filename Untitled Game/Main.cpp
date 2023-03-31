
#include <SFML/graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Player.h"
#include "Animation.h"
#include "Tile.h"
#include "Camera.h"
#include "TileMap.h"
#include "Sword.h"

#include <fstream>
#include <math.h>

using namespace std;
// current goal:

// implement a state system.
//		1) game state will allow the user to play the game, pause the game, and show a blurred out version of visible screen in pause menu
//		2) a main menu state that will allow the user to change the music volume, and adjust other things

// have seperate event loop for menu and levels?
// 
//	RELEVANT:
//	TODO:
//	implement a system where objects are rendered from the top down meaning that if the player is behind something (they are cartesially
//	above it) they will appear behind that object.
//	TODO: make interactable tiles that be interacted with by the player
//
//  TODO: make render function load things into stack but store main map and data in the heap for efficiency

//	TODO: make topdown render work
//	NOTE: First I must change how things with height are rendered into the map.

// TODO: fix walkUpAnim so that cape isnt open

// fix animation class so that upanimation does not flicker
// fix the idle up animation so that the tail goes to side and the cape is flater

// TODO:: make gaps in the earth that the player can fall through for the time being instead of having tall objects

// NOTE: make sure dash only check for collision with walls. So that you can dash past enemies and dash over gaps in ground.

// TODO: make a shadow that besically gets the size of the hitbox of an entity and creates a shadow based on that.

void setKeyPressesKBD(Player& player) {
	player.upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	player.downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	player.leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	player.rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	player.spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

// takes the maps and renders everything one row at a time
// maybe move this to a level.hpp file that handles all the maps and player and enemy date and put renderTopDown() there?
void renderTopDown(sf::Vector2i renderSize, sf::RenderWindow& win, TileMap *layer1, TileMap *layer2, Player *p1) {
	// basically, all assets in the game are rendered in relation to the player to simulate a sense of depth,
	// bottom layer is rendered first always (ground).
	// then we draw things in row by row starting with the top row.
	// if the player is on the row we are currently drawing in, we draw the player aswell.
	// if they are in the canopy layer, they are rendered last.
	for (int i = 0; i < renderSize.y * 2; i++) {
		// this function is currently impossible with how I have the game map 
	}
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
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::LostFocus) {
			window.setFramerateLimit(5);
		}
		if (event.type == sf::Event::GainedFocus) {
			// disables the limit
			window.setFramerateLimit(0);
		}
	}
}

int main() {

	bool gameState = true;

	sf::Vector2f winDim(2048, 1024);
	sf::RenderWindow window(sf::VideoMode(winDim.x, winDim.y), "Untitled Game", sf::Style::Close | sf::Style::Resize);

	// Alll this crap that is being done before game loop can be done elsewhere
	Camera camera;
	camera.setSize(sf::Vector2f(1280, 720));
	camera.zoom(0.25f);
	
	sf::Font roboto;
	if (!roboto.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {
		return -1;
	}
	sf::Text winText;
	winText.setFont(roboto);
	winText.setCharacterSize(10);
	winText.setScale(0.5, 0.5);
	winText.setFillColor(sf::Color::White);
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

	//tile settup ===========

	sf::Vector2i temp_mapSize(8, 8);
	// the 2nd level tilemap
	sf::Texture terrain2;
	if (!terrain2.loadFromFile("Textures/terrainSheettestone16x32.png"))
		return -1;

	int tileTypes2[] = {
		4, 1, 1, 4, 4, 1, 1, 4,
		4, 1, 4, 4, 4, 4, 1, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 1, 4, 4, 4, 4, 1, 4,
		4, 1, 1, 4, 4, 1, 1, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, };
	int logGrid2[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, };

	sf::Vector2u texSize2(16, 32);
	Tile grassCube(terrain2, texSize2 , 0);
	Tile stoneWallCube(terrain2, texSize2, 1);
	Tile boxCube(terrain2, texSize2, 2);
	
	Tile tiles2[] = { grassCube, stoneWallCube, boxCube };
	sf::Vector2u temp_tileSpacing(16, 16);

	TileMap topTileMap(3, tiles2, temp_mapSize, tileTypes2, logGrid2, temp_tileSpacing);
	
	// the terrain tilemap
	sf::Texture terrarin;
	if (!terrarin.loadFromFile("Textures/terrainSheetmk2.png"))
		return -1;

	int tileTypes[] = { 0, 0, 1, 0, 0, 0, 0, 0,
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

	
	sf::Texture fox;
	if (!fox.loadFromFile("Textures/foxSpriteSheetmk1.png"))
		return -1;

	sf::Texture foxShadow;
	if (!foxShadow.loadFromFile("Textures/shadowText.png"))
		return -1;
	sf::Sprite shadowSprite(foxShadow);
	// remember to change the hitbox to match the player size
	
	sf::Texture slash;
	if (!slash.loadFromFile("Textures/slash1.png"))
		return -1;

	Player p1(fox, window, sf::Vector2u(16, 16), 8, 0, 80.f);
	p1.setHitBoxSize(sf::Vector2f(10.f, 10.f), sf::Vector2f(3.f, 6.f));
	p1.setPosition(sf::Vector2f(60.f, 60.f));
	p1.init();
	p1.setState(Player::State::nominal);
	p1.updatePlayerTile(&tileMap);

	Sword s1(p1, slash, sf::Vector2u(32, 16), 1, 0, 0.f);
	s1.initSword();	
	
	sf::Clock mainClock;
	sf::Clock pMoveClock;	
	sf::Clock dtClock;
	while (window.isOpen())
	{
		
		float dt = dtClock.restart().asSeconds();
		processEvents(window);
		// Game.GameState ** change to this later using Game.hpp
		// or not I am not sure If i need a game file tbh
		if (gameState) {
			// if mouse left pressed attack with sword
			
			setKeyPressesKBD(p1);
			window.clear();

			p1.update(dt, &tileMap);
			camera.update(p1, dt);
			window.setView(camera);
			sf::Vector2i renderSize(13, 10);
			
			tileMap.render(p1.curTile, window, renderSize);
			shadowSprite.setPosition(sf::Vector2f(p1.getPosition().x, p1.getPosition().y + 2));
			window.draw(shadowSprite);
			window.draw(p1);
			
			
			s1.update();
			s1.swing(1.f);
			window.draw(s1.hBox);
			window.draw(s1);
			

			//topTileMap.render(p1.curTile, window, renderSize);
			
			
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

			// ignore this::::
			//INFO SETTUP:
			//literally cant for the life of me figure out how to get first two decimal places of a number so this is my solution
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
			window.display();
		}
	}
	return 0;
}
