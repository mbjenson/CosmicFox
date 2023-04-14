#include "GrassLandsLevel.h"

GrassLandsLevel::GrassLandsLevel() {};

int GrassLandsLevel::init(TileMap* map, Player* p1) {
	tileMap = map;
	player = p1;
	tileMap->texDim1 = sf::IntRect(0, 0, 13, 19);
	tileMap->texDim2 = sf::IntRect(16, 0, 16, 32);
	tileMap->texDim3 = sf::IntRect(34, 1, 35, 28);
	//tileMap->texDim4 = sf::IntRect();
	//tileMap->texDim5 = sf::IntRect();
	//tileMap->texDim6 = sf::IntRect();
	return 0;
	
}

int GrassLandsLevel::init(Player* p1) {
	player = p1;

	sf::Texture* terrain1 = new sf::Texture();
	if (!terrain1->loadFromFile("Textures/grassLands3.png"))
		return -1;

	sf::Texture* terrain2 = new sf::Texture();
	if (!terrain2->loadFromFile("Textures/grassLands3.png"))
		return -1;

	sf::Texture* rocks = new sf::Texture();
	if (!rocks->loadFromFile("Textures/rocks1.png"))
		return -1;

	int* logicGrid2 = new int[2304];
	read_ints("Assets/Levels/MapFiles/Map1Logic.csv", logicGrid2);
	int* tileTypes1 = new int[2304];
	read_ints("Assets/Levels/MapFiles/Map1Layer1.csv", tileTypes1);
	int* tileTypes2 = new int[2304];
	read_ints("assets/Levels/MapFiles/Map1Layer2.csv", tileTypes2);
	int* tileTypes3 = new int[2304];
	read_ints("assets/Levels/MapFiles/Map1Layer3.csv", tileTypes3);

	sf::Vector2i mapDimChunks1(3, 3);

	tileMap = new TileMap(tileTypes1, tileTypes2, tileTypes3, logicGrid2,
		mapDimChunks1, terrain1, terrain2, rocks);

	tileMap->texDim1 = sf::IntRect(0, 0, 13, 19);
	tileMap->texDim2 = sf::IntRect(16, 0, 16, 32);
	tileMap->texDim3 = sf::IntRect(34, 1, 35, 28);

	tileMap->init();
	tileMap->updatePlayerChunk(player->getPosition());
	tileMap->updateTexMap();

	return 0;

}

