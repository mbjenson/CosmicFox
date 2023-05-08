#include "CrashLevel.h"

CrashLevel::CrashLevel(Player* player) {
	init(player);
}

int CrashLevel::init(Player* p1) {

	player = p1;

	playerSpawn = sf::Vector2f(217,168);

	sf::Texture* terrain1 = new sf::Texture();
	if (!terrain1->loadFromFile("Textures/grassLands3.png"))
		return -1;

	sf::Texture* terrain2 = new sf::Texture();
	if (!terrain2->loadFromFile("Textures/grassLands3.png"))
		return -1;

	sf::Texture* rocks = new sf::Texture();
	if (!rocks->loadFromFile("Textures/inter2.png"))
		return -1;

	int* logicGrid2 = new int[1024];
	read_ints("Assets/Levels/MapFiles/CrashLevel_Logic.csv", logicGrid2);
	int* tileTypes1 = new int[1024];
	read_ints("Assets/Levels/MapFiles/CrashLevel_Layer1.csv", tileTypes1);
	int* tileTypes2 = new int[1024];
	read_ints("assets/Levels/MapFiles/CrashLevel_Layer2.csv", tileTypes2);
	int* tileTypes3 = new int[1024];
	read_ints("assets/Levels/MapFiles/CrashLevel_Layer3.csv", tileTypes3);

	sf::Vector2i mapDimChunks1(2, 2);

	tileMap = new TileMap(tileTypes1, tileTypes2, tileTypes3, logicGrid2,
		mapDimChunks1, terrain1, terrain2, rocks);

	tileMap->texDim1 = sf::IntRect(143, 9, 44, 101);
	tileMap->offsetDim1 = sf::Vector2i(0, 4);
	tileMap->texDim2 = sf::IntRect(28, 1, 25, 38);
	tileMap->offsetDim2 = sf::Vector2i(9, 17);
	tileMap->texDim3 = sf::IntRect(40, 42, 18, 65);
	tileMap->offsetDim3 = sf::Vector2i(1, 49);

	usingShader = false;

	if (!tileMap->bgTex.loadFromFile("Textures/clouds.png"))
		return -1;

	tileMap->init();
	tileMap->updatePlayerChunk(player->getPosition());
	tileMap->updateTexMap();

	tileMap->bgOffset = sf::Vector2f(-100.f, -30.f);
	

	return 0;
}