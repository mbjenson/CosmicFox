#include "deathScreen.h"

deathScreen::deathScreen() {}

int deathScreen::init() {
	
	screenTex.create(2000, 2000);

	if (!playBTex.loadFromFile("Textures/playerButton.png"))
		return -1;
	if (!quitBTex.loadFromFile("Textures/quitButton.png"))
		return -1;
	if (!deathTex.loadFromFile("Textures/deathText.png"))
		return -1;

	text.setTexture(deathTex);
	text.setOrigin(deathTex.getSize().x / 2, deathTex.getSize().y / 2);
	text.setPosition(sf::Vector2f(951, 540));
	text.setScale(15.f, 15.f);

	screen.setTexture(screenTex);

	playB.setTexture(playBTex);
	playB.setTextureRect(sf::IntRect(0, 0, 30, 14));
	playB.setScale(sf::Vector2f(15.f, 15.f));
	playB.setPosition(sf::Vector2f(450.f, 700.f));

	quitB.setTexture(quitBTex);
	quitB.setTextureRect(sf::IntRect(0, 0, 30, 14));
	quitB.setScale(sf::Vector2f(15.f, 15.f));
	quitB.setPosition(sf::Vector2f(1050.f, 700.f));

	//sf::Music music;
	//if (!music.openFromFile("Sounds/gameAmbience1.wav"))
	//	return -1;
	//music.setPlayingOffset(sf::seconds(5.f));
	//music.play();
	//music.play();
	//music.setVolume(50.f);


	return 0;
}

int deathScreen::update(sf::RenderWindow& win) {
	win.draw(screen);
	win.draw(text);

	if (playB.getGlobalBounds().contains(sf::Vector2f(win.mapPixelToCoords(sf::Mouse::getPosition())))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			return 1;
		}
		playB.setTextureRect(sf::IntRect(0, 14, 30, 14));
	}
	else {
		playB.setTextureRect(sf::IntRect(0, 0, 30, 14));
	}
	if (quitB.getGlobalBounds().contains(sf::Vector2f(win.mapPixelToCoords(sf::Mouse::getPosition())))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			return 2;
		}
		quitB.setTextureRect(sf::IntRect(0, 14, 30, 14));
	}
	else {
		quitB.setTextureRect(sf::IntRect(0, 0, 30, 14));
	}
	win.draw(playB);
	win.draw(quitB);
	return 0;
}