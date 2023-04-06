#pragma once
#include <SFML/Graphics.hpp>
#include "MappingFunctions.h"

using namespace std;


/*
Finish this in the future


*/
class MapEditor
{
public:

	MapEditor(sf::Vector2i worldTileDim, sf::Texture& _tileSheet, std::string _fileName);

	void updateMap();

	void init();

	void render(sf::RenderWindow& win);

	void updateSideBar();

	void processEvents(sf::RenderWindow& win);

	void getInput();

	bool placeTile();

	void updateSelection();
	
	void select();

	void moveView();
	
	int selection = 0;
	sf::Sprite selectedTile;

	sf::View view;
	float moveSpeed = 1;

	std::string fileName;
	sf::Texture* tileSheet;
	sf::Vector2i worldDimTiles;

	sf::Sprite sideBar;
	sf::IntRect barBounds;
	int tileView = 10;
	
	sf::RenderTexture map;
	std::vector<int>* mapVec;
	int tileSize = 16;
};


