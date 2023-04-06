#include "MapEditor.h"

MapEditor::MapEditor(sf:: Vector2i worldTileDim, sf::Texture& _tileSheet, std::string _fileName) {
	fileName = _fileName;
	tileSheet = &_tileSheet;
	worldDimTiles = worldTileDim;
}

void MapEditor::init() {
	map.create(worldDimTiles.x * tileSize, worldDimTiles.y * tileSize);
	sideBar.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize * 26));
	sideBar.setTexture(*tileSheet);
	mapVec = new std::vector<int>(worldDimTiles.x * worldDimTiles.y, 0);
	selectedTile.setTexture(*tileSheet);
	selectedTile.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
}

void MapEditor::updateMap() {
	for (int y = 0; y < worldDimTiles.y; y++) {
		for (int x = 0; x < worldDimTiles.x; x++) {
			int curTile = mapVec->at(x + y * worldDimTiles.x);
			//int curTile2 = layer2Types[x + y * chunkSize * mapDimChunks.x];
			sf::Sprite tempSpr1(*tileSheet);
			tempSpr1.setTextureRect(sf::IntRect(0, curTile * tileSize, tileSize, tileSize));
			tempSpr1.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
			//sf::Sprite tempSpr2(*layer2Texture);
			//tempSpr2.setTextureRect(sf::IntRect(0, curTile2 * tileSize, tileSize, tileSize));
			//tempSpr2.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
			map.draw(tempSpr1);
			//mapTex.draw(tempSpr2);
		}
	}
	map.display();
}

void MapEditor::render(sf::RenderWindow& win) {
	// draw & position sideBar
	sideBar.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	win.draw(sideBar);
	// update selected tile type and draw it at the corrected tile location
	selectedTile.setPosition(screenToWorld(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, sf::Vector2f(view.getCenter().x / 2, view.getCenter().y / 2)));
	win.draw(selectedTile);

	sf::Sprite mapSpr(map.getTexture());
	win.draw(mapSpr);
}

void MapEditor::getInput() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (sideBar.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
			printf("inside sideBar");
		}
		else {
			printf("outside sideBar");
		}
	}
	
}

void MapEditor::processEvents(sf::RenderWindow& window) {
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
		if (event.type == sf::Event::MouseWheelMoved) {
			if (sideBar.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
				if (sf::Event::MouseWheelScrollEvent().delta > 0) {
					if (sideBar.getTextureRect().top + sideBar.getTextureRect().height < sideBar.getTexture()->getSize().y) {
						sideBar.setTextureRect(sf::IntRect(0, sideBar.getTextureRect().top + (1 + (10 / sf::Event::MouseWheelEvent().delta)),
							sideBar.getTextureRect().width, sideBar.getTextureRect().height));
					}
				}
				if (sf::Event::MouseWheelScrollEvent().delta < 0) {
					if (sideBar.getTextureRect().top > 0) {
						sideBar.setTextureRect(sf::IntRect(0, sideBar.getTextureRect().top - (1 + (10 / sf::Event::MouseWheelEvent().delta)),
							sideBar.getTextureRect().width, sideBar.getTextureRect().height));
					}
				}
			}
		}
		if (event.type == sf::Event::MouseLeft) {
			updateSelection();
		}
		// if mouse on side bar
		
		// if mouse on map
		/*
		else {
			if (event.type == sf::Event::MouseWheelMoved) {
				if (sf::Event::MouseWheelEvent().delta != 0) {
					view.zoom(1 + (10 / sf::Event::MouseWheelEvent().delta));
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (placeTile()) {
					updateMap();
				}

			}
		}
		*/
	}
	
}

void MapEditor::moveView() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		view.move(-moveSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		view.move(0, -moveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		view.move(moveSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		view.move(0, moveSpeed);
	}
}

// called by process events
bool MapEditor::placeTile() {
	sf::Vector2i mousePos(sf::Mouse::getPosition().x / tileSize, sf::Mouse::getPosition().y / tileSize);
	if (mousePos.x < 0 || mousePos.x > worldDimTiles.x || mousePos.y < 0 || mousePos.y > worldDimTiles.y)
		return false;
	else {
		// i think this should check if the operation was completed successfully
		if (mapVec->at(mousePos.x + mousePos.y * worldDimTiles.x) = selection)
			return true;
	}
}

// display the selection of tile on the mouse of the user
// assume mouse is on the sideBar
void MapEditor::updateSelection() {
	int screenIndex = sf::Mouse::getPosition().y / tileSize;
	selection = screenIndex + sideBar.getTextureRect().top;
	selectedTile.setTextureRect(sf::IntRect(0, selection * tileSize, tileSize, tileSize));
}

void MapEditor::select() {

}