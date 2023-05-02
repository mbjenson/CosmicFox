#include "GrassLandsLevel.h"

GrassLandsLevel::GrassLandsLevel(Player* player) {
	init(player);
};

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

	if (!sBuf.loadFromFile("Sounds/GhostDeath.wav")) {
		return -1;
	}
	s1.setBuffer(sBuf);
	s1.setVolume(40.f);

	if (!tileMap->bgTex.loadFromFile("Textures/beachBG.png"))
		return -1;

	

	tileMap->init();
	tileMap->updatePlayerChunk(player->getPosition());
	tileMap->updateTexMap();
	
	tileMap->bg.setScale(sf::Vector2f(1.3f, 1.3f));

	// initialize enemies
	if (!ghostTex.loadFromFile("Textures/enemySpriteSheetmk1.png"))
		return -1;

	

	sf::Vector2u ghostSize(24, 24);
	GhostEnemy g1(&ghostTex, ghostSize, 1, 0, 0.f);
	GhostEnemy g2(&ghostTex, ghostSize, 1, 0, 0.f);
	GhostEnemy g3(&ghostTex, ghostSize, 1, 0, 0.f);
	GhostEnemy g4(&ghostTex, ghostSize, 1, 0, 0.f);
	GhostEnemy g5(&ghostTex, ghostSize, 1, 0, 0.f);
	GhostEnemy g6(&ghostTex, ghostSize, 1, 0, 0.f);
	GhostEnemy g7(&ghostTex, ghostSize, 1, 0, 0.f);
	GhostEnemy g8(&ghostTex, ghostSize, 1, 0, 0.f);

	g1.initGhost();
	g2.initGhost();
	g3.initGhost();
	g4.initGhost();
	g5.initGhost();
	g6.initGhost();
	g7.initGhost();
	g8.initGhost();
	
	g1.setSpawn(sf::Vector2f(350.f, 500.f));
	g2.setSpawn(sf::Vector2f(360.f, 600.f));
	g3.setSpawn(sf::Vector2f(370.f, 700.f));
	g4.setSpawn(sf::Vector2f(100.f, 400.f));
	g5.setSpawn(sf::Vector2f(390.f, 1000.f));
	g6.setSpawn(sf::Vector2f(200.f, 1010.f));
	g7.setSpawn(sf::Vector2f(358.f, 1200.f));
	g8.setSpawn(sf::Vector2f(600.f, 300.f));
	
	g1.setPosition(g1.spawnpoint);
	g2.setPosition(g2.spawnpoint);
	g3.setPosition(g3.spawnpoint);
	g4.setPosition(g4.spawnpoint);
	g5.setPosition(g5.spawnpoint);
	g6.setPosition(g6.spawnpoint);
	g7.setPosition(g7.spawnpoint);
	g8.setPosition(g8.spawnpoint);

	eVec.push_back(g1);
	eVec.push_back(g2);
	eVec.push_back(g3);
	eVec.push_back(g4);
	eVec.push_back(g5);
	eVec.push_back(g6);
	eVec.push_back(g7);
	eVec.push_back(g8);
	
	playerSpawn = sf::Vector2f(400.f, 28.f);
	
	return 0;
}

