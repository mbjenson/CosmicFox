#include "PauseButton.h"

PauseButton::PauseButton(){}

int PauseButton::init() {
	if (!bTex.loadFromFile("Textures/pauseButton.png"))
		return -1;
	ps.setTexture(bTex);
	//ps.setScale(.f, 20.f);

}

int PauseButton::update(sf::RenderWindow& win) {
	sf::View temp = win.getView();
	ps.setTextureRect(sf::IntRect(0, 0, 16, 16));
	ps.setPosition((temp.getCenter().x + temp.getSize().x / 2) - 18.f, (temp.getCenter().y - temp.getSize().y / 2) + 2.f);
	if (ps.getGlobalBounds().contains(sf::Vector2f(win.mapPixelToCoords(sf::Mouse::getPosition())))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return 1;
		}
		ps.setTextureRect(sf::IntRect(0, 16, 16, 16));
	}
	else {
		ps.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	win.draw(ps);
	return 0;
}