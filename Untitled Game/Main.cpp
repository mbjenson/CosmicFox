
#include <SFML/graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <math.h>
#include <iostream>
#include "ResHandler.h"
#include "PauseButton.h"
#include "deathScreen.h"
#include "Menu.h"
#include "Player.h"
#include "Camera.h"
#include "GrassLandsLevel.h"
#include "HudBar.h"
#include "DashMeter.h"
#include "Spirit.h"
#include "IntroLevel.h"
#include "CrashLevel.h"

using namespace std;

bool DEBUG;
sf::Clock GLOBAL_GAME_CLOCK;

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
		quit,
	};

	State state = State::menu;

	sf::Vector2f winDim(2560, 1440);
	sf::RenderWindow window(sf::VideoMode(winDim.x, winDim.y), "Untitled Game", sf::Style::Close | sf::Style::Fullscreen);
	
	sf::View menuView;
	menuView.setCenter(951, 540);
	menuView.setSize(1920, 1080);

	Camera camera;
	camera.setSize(sf::Vector2f(1920, 1080));
	camera.zoom(0.15f);

	sf::Font roboto;
	
	if (!roboto.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {
		return -1;
	}
	
	sf::Text winText;
	winText.setFont(roboto);
	winText.setCharacterSize(10);
	winText.setScale(0.5, 0.5);
	winText.setFillColor(sf::Color::White);

	sf::Text hudText;
	hudText.setFont(roboto);
	hudText.setCharacterSize(15);
	hudText.setScale(0.5, 0.5);
	hudText.setFillColor(sf::Color(200, 150, 0));
	
	sf::Texture fox;
	if (!fox.loadFromFile("Textures/foxSpriteSheetmk2.png"))
		return -1;
	
	sf::Texture vignette;
	if (!vignette.loadFromFile("Textures/vignetteShadow.png"))
		return -1;

	sf::Sprite vig(vignette);
	
	vig.setScale(0.728f, 0.52f); // old : 0.7, 0.5
	
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

	// vector of null levels. A level is initialized and loaded when the player advances to a given level.
	vector<Level*> levelVec(3);
	int curLevelIndex = 0;
	//int curLevelIndex = 0;
	levelVec.at(0) = new CrashLevel(&p1);
	

	Level* curLevel;
	curLevel = levelVec.at(curLevelIndex);
	p1.setPosition(curLevel->playerSpawn);

	sf::Music music;
	if (!music.openFromFile("Sounds/gameAmbience1.wav"))
		return -1;
	music.play();
	music.setVolume(70.f);
	music.setLoop(true);

	sf::BlendMode none;

	Menu mainMenu;
	mainMenu.init();

	PauseButton pauseB;
	pauseB.init();
	
	deathScreen deathMenu;

	sf::Texture win;
	win.loadFromFile("Textures/win.png");
	sf::Sprite winScreen(win);

	winScreen.setScale(2.5f, 2.5f);
	int endgame = 0;

	// GAME LOOP
	sf::Clock mainClock;
	sf::Clock dtClock;
	while (window.isOpen())
	{
		float dt = dtClock.restart().asSeconds();
		processEvents(window);
		
		if (state == State::menu) {
			window.setView(menuView);
			window.clear();
			int result = mainMenu.update(window);
			if (result == 1) { // play game
				state = State::game;
			}
			if (result == 2) { // quit game
				state = State::quit;
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
				state = State::quit;
			}
			window.display();
		}
		if (state == State::quit) {
			window.close();
		}
		if (state == State::game) {
			
			// update bg position
			
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
			vig.setPosition(sf::Vector2f(camera.getCenter().x - vig.getGlobalBounds().width / 2, camera.getCenter().y - vig.getGlobalBounds().height / 2));
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
					levelVec.at(curLevelIndex) = new IntroLevel(&p1);
				}
				if (curLevelIndex == 2) {
					levelVec.at(curLevelIndex) = new GrassLandsLevel(&p1);
				}
				curLevel = levelVec.at(curLevelIndex);
				p1.setPosition(curLevel->playerSpawn);
				levelTransition(&window);
			}

			if (p1.FLAG_DEAD) {
				if (p1.deathTimer.getElapsedTime().asMilliseconds() > p1.deathRestTime) {
					state = State::death;
				}
			}
			
			if (curLevelIndex == 2 && levelVec.at(curLevelIndex)->eVec.empty()) {
				if (endgame < 2000) {
					winScreen.setPosition(camera.getCenter().x - camera.getSize().x / 4, camera.getCenter().y - camera.getSize().y / 2);
					window.draw(winScreen);
					endgame++;
				}
			}
			
			if (curLevelIndex == 2) {
				
				int remEnemies = levelVec.at(curLevelIndex)->eVec.size();
				int score = 100 * (curLevel->numEnemies - remEnemies);
				string strScore = to_string(score);
				hudText.setPosition(sf::Vector2f(camera.getCenter().x - 17.f, camera.getCenter().y + 5 - camera.getSize().y / 2));
				hudText.setString("score: " + strScore);
				window.draw(hudText);
			}
			
			if (DEBUG) { // press 'G' to show debugging information.

				string xPlayerCord = roundedString(2, p1.getPosition().x);
				string yPlayerCord = roundedString(2, p1.getPosition().y);

				winText.setPosition(sf::Vector2f(camera.getCenter().x + 5 - camera.getSize().x / 2, camera.getCenter().y + 15 - camera.getSize().y / 2));
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