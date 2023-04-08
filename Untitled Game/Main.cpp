
#include <SFML/graphics.hpp>
#include <SFML/OpenGL.hpp>


#include "Player.h"
#include "Animation.h"
#include "Tile.h"
#include "Camera.h"
#include "Sword.h"
#include "HudBar.h"
#include "TileMap.h"
#include "ResHandler.h"
#include "GrassLandsLevel.h"

#include <fstream>
#include <math.h>
#include <iostream>
//#include <thread>

using namespace std;
bool DEBUG;

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
* ->	Implement a way that tiles can have animations with tilemapmk2. cant use the current animation class
* 
* ->	Move collision check to the entity class
* 
* 
*/

// TODO:

// first:	Move the collision check function to entity class:
//			This will require that the "finalVel" vec is moved to the entity class.

//  Entity shadows

//  enemies:
//		Add enemy class to game
//		In the level class, have a component that handles all the enemies in the game.
//		To efficiently check enemy positions around player, an array must be used.
//		In this array, 0 represents empty space while numbers > 0 represent different types of enemies.
//		When I pushback the vector of entities / enemies in my game, have a way to update the array of positions.

// Sword combo:
//		add to sword class a function that will allow for 3 different hboxes maybe.
//		make it so that when you use the sword, you are slowed and move forward slightly
//		make the sword combo 3 things long.

// LightMap
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
	sf::Vector2f winDim(2048, 1024);
	sf::RenderWindow window(sf::VideoMode(winDim.x, winDim.y), "Untitled Game", sf::Style::Close | sf::Style::Resize);

	sf::Shader shader;
	if (!shader.loadFromFile("Shaders/light_test.frag", sf::Shader::Fragment)) {
		return -1;
	}
	sf::Texture black;
	if (!black.loadFromFile("Textures/black.png")) {
		return -1;
	}
	sf::Sprite box(black);
	
	sf::Texture screen;
	screen.create(winDim.x, winDim.y);
	sf::Sprite windowS(screen);
	sf::Clock mainClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed())
				window.close();
		}
		window.clear();
		window.draw(windowS, &shader);
		window.display();
	}
}
*/

int main() {

	bool gameState = true;

	sf::Vector2f winDim(2048, 1024);
	sf::RenderWindow window(sf::VideoMode(winDim.x, winDim.y), "Untitled Game", sf::Style::Close | sf::Style::Resize);

	Camera camera;
	camera.setSize(sf::Vector2f(1280, 720));
	camera.zoom(0.24f);
	//camera.zoom(1.f);

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
	sf::Texture foxShadow;
	if (!foxShadow.loadFromFile("Textures/shadowText.png"))
		return -1;
	sf::Sprite shadowSprite(foxShadow);

	Player p1(fox, window, sf::Vector2u(16, 16), 8, 0, 80.f);
	p1.setPosition(sf::Vector2f(150.f, 150.f));
	p1.init();
	p1.setState(Player::State::nominal);
	/*
	// the terrain tilemap
	sf::Texture* terrain1 = new sf::Texture();
	if (!terrain1->loadFromFile("Textures/grassLands2.png"))
		return -1;

	sf::Texture* terrain2 = new sf::Texture();
	if (!terrain2->loadFromFile("Textures/grassLands2.png"))
		return -1;

	sf::Texture* rocks = new sf::Texture();
	if (!rocks->loadFromFile("Textures/rocks1.png"))
		return -1;
	// setting up the tilemapmk2
	

	int* logicGrid2 = new int[2304];
	read_ints("Assets/Levels/MapFiles/Map1Logic.csv", logicGrid2);
	int* tileTypes1 = new int[2304];
	read_ints("Assets/Levels/MapFiles/Map1Layer1.csv", tileTypes1);
	int* tileTypes2 = new int[2304];
	read_ints("assets/Levels/MapFiles/Map1Layer2.csv", tileTypes2);
	int* tileTypes3 = new int[2304];
	read_ints("assets/Levels/MapFiles/Map1Layer3.csv", tileTypes3);
	sf::Vector2i mapDimChunks1(3, 3);

	TileMap* newMap = new TileMap(	tileTypes1, tileTypes2, tileTypes3, logicGrid2,
									mapDimChunks1, terrain1, terrain2, rocks);
	//TileMapmk2* newMap = new TileMapmk2(tileTypes1, tileTypes2, logicGrid1, mapDimChunks1, terrain1, terrain2);
	newMap->init();
	newMap->updatePlayerChunk(p1.getPosition());
	newMap->updateTexMap();

	GrassLandsLevel level1;
	level1.init(newMap, &p1);
	*/

	GrassLandsLevel newLevel;
	newLevel.init(&p1);

	sf::Clock dtClock;
	while (window.isOpen())
	{
		float dt = dtClock.restart().asSeconds();
		processEvents(window);
		// Game.GameState ** change to this later using Game.hpp
		if (gameState) {
			setKeyPressesKBD(p1);
			window.clear();

			p1.update(dt, newLevel.tileMap);
			camera.update(p1, dt);
			window.setView(camera);
			
			//if (newMap->checkForUpdate(p1.getPosition())) {
			//	newMap->updateTexMap();
			//	newMap->updatePlayerChunk(p1.getPosition());
			//}
			//sf::Sprite mapSprite(newMap->getMapTex()->getTexture());

			//window.draw(mapSprite);
			//shadowSprite.setPosition(sf::Vector2f(p1.getPosition().x - 8, p1.getPosition().y - 6));
			//window.draw(shadowSprite);
			//window.draw(p1);
			
			newLevel.render(window);
			
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
			}

			window.display();
		}
	}
	return 0;
}



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