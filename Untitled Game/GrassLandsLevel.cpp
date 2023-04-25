#include "GrassLandsLevel.h"

GrassLandsLevel::GrassLandsLevel(Player* player) {
	init(player);
};

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
	usingShader = false;
	// Map 1 setup:
	sf::Texture* terrain1 = new sf::Texture();
	if (!terrain1->loadFromFile("Textures/grassLands3.png"))
		return -1;

	sf::Texture* terrain2 = new sf::Texture();
	if (!terrain2->loadFromFile("Textures/grassLands3.png"))
		return -1;

	sf::Texture* rocks = new sf::Texture();
	if (!rocks->loadFromFile("Textures/inter.png"))
		return -1;

	

	int* logicGrid2 = new int[3840];
	read_ints("Assets/Levels/MapFiles/Map1Logic.csv", logicGrid2);
	int* tileTypes1 = new int[3840];
	read_ints("Assets/Levels/MapFiles/Map1Layer1.csv", tileTypes1);
	int* tileTypes2 = new int[3840];
	read_ints("assets/Levels/MapFiles/Map1Layer2.csv", tileTypes2);
	int* tileTypes3 = new int[3840];
	read_ints("assets/Levels/MapFiles/Map1Layer3.csv", tileTypes3);

	sf::Vector2i mapDimChunks1(3, 5);

	tileMap = new TileMap(tileTypes1, tileTypes2, tileTypes3, logicGrid2,
		mapDimChunks1, terrain1, terrain2, rocks);

	tileMap->texDim1 = sf::IntRect(1, 1, 25, 38);
	tileMap->offsetDim1 = sf::Vector2i(9, 17);
	tileMap->texDim2 = sf::IntRect(28, 1, 25, 38);
	tileMap->offsetDim2 = sf::Vector2i(9, 17);
	tileMap->texDim3 = sf::IntRect(53, 0, 21, 33);
	tileMap->offsetDim3 = sf::Vector2i(4, 12);
	tileMap->texDim4 = sf::IntRect(13, 42, 20, 79);
	tileMap->offsetDim4 = sf::Vector2i(3, 49);
	tileMap->texDim5 = sf::IntRect(77, 32, 51, 97);
	tileMap->offsetDim5 = sf::Vector2i(2, 45);
	tileMap->texDim6 = sf::IntRect(40, 42, 18, 65);
	tileMap->offsetDim6 = sf::Vector2i(1, 49);

	if (!tileMap->bgTex.loadFromFile("Textures/planet.png"))
		return -1;

	tileMap->init();
	tileMap->updatePlayerChunk(player->getPosition());
	tileMap->updateTexMap();

	

	// initialize enemies
	if (!ghostTex.loadFromFile("Textures/enemySpriteSheetmk1.png"))
		return -1;

	GhostEnemy g1(&ghostTex, sf::Vector2u(24, 24), 1, 0, 0.f);
	g1.initGhost();
	g1.setSpawn(sf::Vector2f(200.f, 200.f));
	g1.setPosition(g1.spawnpoint);
	eVec.push_back(g1);
	
	
	//g1.init();
	//g1.setPosition(sf::Vector2f(200.f, 200.f));
	/*
	sf::Vector2i enemyTexDim(24, 24);
	Enemy e1(&enemyT, sf::Vector2f(16.f, 16.f), enemyTexDim, 1, 0, 0.f);
	e1.init();
	e1.setPosition(150.f, 60.f);
	
	Enemy e2(&enemyT, sf::Vector2f(16.f, 16.f));
	e2.init();
	e2.setPosition(200.f, 200.f);
	*/
	//eVec.push_back(g1);
	
	
	return 0;

}

