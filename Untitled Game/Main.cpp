
#include <SFML/graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Player.h"
#include "Animation.h"
#include "Tile.h"
#include "Camera.h"
#include "TileMap.h"

#include <fstream>
#include <math.h>


using namespace std;
// current goal:
// sort out how I am going to render a tile map with different textures, collidable objects, and the likes.
// 
// idea:    each tile will be an sf::quad and will have a texture assigned to it.
//			We will use a vector of quads.
//			we will read input from the file into an array
//			we will only render the ones that are within a certain distance of the player
//			otherwise the game will lag immensly (culling)

// implement a state system.
//		1) game state will allow the user to play the game, pause the game
//		2) a main menu state that will allow the user to change the music volume, and adjust other things

// IDEA:
// this game is based in space.
// there are floating islands connected by bridges that you travers and fight enemies on.
// use paralax effect to make medeorties, stars, and other things move at different rates to create
//		a sense of vast space.
// I LIKE THIS

//IDEA:
// use boolean variables to control game state. have a menu that, if play is pressed, a bool will change
// and when the loop checks, it will draw a map onto the window with the player and everything else.
// If the menu is drawn it will not load the player or anything else just the menu.

// have seperate event loop for menu and levels?

// COMPLETE:
//TODO: (CHECKMARK!)
// create an animation class which handles texturesheet and updating sprite information
// implement that into the tile and entity class so that they can be animated simply
// TODO: (CHECKMARK!)
// implement hit box size which can be different from the actual size of the texture. then use this
// for collision detection. this makes the hitbox and the size of the texture exclusive.
// TODO: (CHECKMARK!)
// fix issue with collisions where if between two collidable tiles, if pushing on left side wall, moving up and down is
// //		not possible without moving away from wall then moving up or down.
// TODO: (CHECKMARK!)
// limit the walk velocity in the different directions using the direction the player is currently facing (N, E, S, W)
// the old function broke since I implemented collisions
// 
//	TODO: (CHECKMARK!)
//	implement a system where objects can have heights. this means their bases will have hitboxes but they can be rendered above the ground.
//	this will create a sense of depth. So example, a box will appear to have a shorter front than top because the camera
//	is looking down from below.
//	idea 1) *bad
//		The hitbox for the tile can be specified by supplying a floatrect to the tile constructor.
//		the textureDim, which will be used for rendering is already specified.
//	idea 2)
//		There will be another level of rendering which renders upper level things like trees, houses, and other things.
//		Tilemap is for the ground level things, another class called (*IDK YET*) will be created and used to draw the textures
//		on the board.
// idea 3)
//		simply add another slot for a texture in the tile object. Then, when the tilemap is rendered in, the tiles are rendered from top to
//		bottom so that if the player is behind something it will appear behind it.
// 
// BACKBURNER:
//	TODO: (backburner....)
//	implement the animation class differently into the tile class, 
//	current issue: unable to update the animations of all tiles simulataneously
//	find a way to do this.
//	NOTE: animating tiles would be very difficult to do for an entire board. if i need to animate a tile i can do it individually


// TODO: 
// find a way to animate the players rotation to the new movement direction
//		 idea: (pretty easy and probably correct) (however, knowing my math skills probably not)
//			use the animation class, have a desired angle that, when updated, cues an animation (or a mathematical rotation of the player)
//			that shows the player rotating towards that angle, every frame, the game checks 
//			if the current angle is equal to that angle and if not, the sprite will continue to rotate towards that angle, if and when
//			that angle is updated, the new angle will be set as the desired angle.
//			the equation will take the difference between the desired angle and current angle and multiply that by a constant value
//			which will make the player spin faster if farther away from the desired angle and slower if closer to the desired angle

// RELEVANT:
//	TODO:
//	implement a system where objects are rendered from the top down meaning that if the player is behind something (they are cartesially
//	above it) they will appear behind that object.

//	TODO: 
//	Shaders:
// 
//	TODO:
//	create a projectile class which has a sprite
//	implement simple physics into the class and allow the player to weild some type of projectile shooting thing
//		NOTE: check if (projectile.getglobalbounds().intersects( a wall, an enemy, or something) and make the projectile
//				dissapear or bounce or stop then do damage to the enemey, 
// 
// TODO: make interactable tiles that be interacted with by the player
// 
// TODO: fix player dash so it is a function of time. and add a cooldown.
//
// TODO: make render function load things into stack but store main map and data in the heap for efficiency
//


// TODO:
// limit the dash velocity like the walk velocity
// add limdashvel to update
// update the player update function so that It adds dashing to the final vel before moving the player 



//CURRENTLY:
// 1) fix apply friction
// 2) get rid of cluttered code that is unused like setDiagBool (could be useful actually)
// 3) rejoice, for the Lord my God is with me
// 4) rejoice yet again because I finally understand how to 



void setKeyPresses(Player& player) {
	player.upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	player.downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	player.leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	player.rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	player.spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

// takes the maps and renders everything one row at a time
// maybe move this to a level.hpp file that handles all the maps and player and enemy date and put renderTopDown() there?
void renderTopDown(sf::RenderWindow& win) {
	return;
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

	// Shader settup
	if (!sf::Shader::isAvailable())
		return -1;

	sf::Shader sh1;
	if (!sh1.loadFromFile("Shaders/test1.frag", sf::Shader::Fragment))
		return -1;


	sf::Texture blackT;
	if (!blackT.loadFromFile("Textures/black.png"))
		return -1;
	sf::Sprite lightS(blackT);

	lightS.setScale(
		winDim.x / lightS.getGlobalBounds().width,
		winDim.y / lightS.getGlobalBounds().height
	);

	//tile and player settup ===========
	sf::Texture square;
	if (!square.loadFromFile("Textures/playerCube16.png"))
		return -1;

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
	if (!terrarin.loadFromFile("Textures/tileSheet16mk1.png"))
		return -1;

	int tileTypes[] = { 0, 0, 1, 0, 0, 0, 0, 0,
						1, 1, 0, 0, 1, 0, 1, 0,
						1, 0, 0, 0, 1, 1, 0, 1,
						0, 0, 0, 0, 0, 0, 1, 1,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						1, 1, 1, 1, 1, 1, 1, 1,
						0, 0, 0, 0, 0, 0, 0, 0,	};
	int logGrid[] = {	
		0, 0, 0, 0, 0, 0, 0, 0,	
		0, 1, 1, 0, 0, 1, 1, 0, 
		0, 1, 0, 0, 0, 0, 1, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 1, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 0, 0, 1, 1, 0, 
		0, 0, 0, 0, 0, 0, 0, 0,	};

	sf::Vector2u groundTexSize(16, 16);
	Tile grass(terrarin, groundTexSize, 0);
	Tile grassStone(terrarin, groundTexSize, 1);
	Tile stoneWall(terrarin, groundTexSize, 2);
	Tile stone(terrarin, groundTexSize, 3);
	Tile stairsR(terrarin, groundTexSize, 4);
	Tile stairsL(terrarin, groundTexSize, 5);

	Tile tiles1[] = { grass, grassStone, stoneWall, stone, stairsR, stairsL };

	sf::Vector2u temp_tileSize(16, 16);
	TileMap tileMap(6, tiles1, temp_mapSize, tileTypes, logGrid, temp_tileSize);

	sf::Texture grasst;
	if (!grasst.loadFromFile("Textures/terrainSheettestone16x32.png"))
		return -1;

	Tile grassT(grasst, sf::Vector2u(16, 32), 0);
	grassT.setPosition(sf::Vector2f(0.f, 0.f));

	Player p1(square, window, sf::Vector2u(16, 16), 1, 0, 0.1);
	p1.tSprite.setScale(0.60, 0.60);
	p1.setPosition(sf::Vector2f(45.f, 45.f));
	p1.init();
	p1.setState(Player::State::nominal);
	p1.updatePlayerTile(&tileMap);
	
	//int testFrameiterator = 0;
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
			

			/*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				p1.walkNorth(dt);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				p1.walkWest(dt);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				p1.walkSouth(dt);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				p1.walkEast(dt);
			*/
			/*
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				p1.attack();
			*/
			// if enough frames have passed then perform action and reset counter else do nothing
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			//	p1.dash(mainClock.getElapsedTime().asSeconds(), dt);
			//}
			/*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				p1.spacePressed = true;
				p1.upPressed = true;
				p1.rightPressed = true;
			}
			*/
			
			setKeyPresses(p1);
			window.clear();

			//if (p1.spacePressed)
			//	int x = 1;

			p1.update(dt, &tileMap);
			camera.update(p1, dt);
			window.setView(camera);
			sf::Vector2i renderSize(13, 8);
			tileMap.render(p1.curTile, window, renderSize);
			window.draw(p1);
			topTileMap.render(p1.curTile, window, renderSize);
			
			/*
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

			window.display();
		}
	}
	return 0;
}
