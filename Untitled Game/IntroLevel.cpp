#include "IntroLevel.h"

IntroLevel::IntroLevel(Player* player) {
	init(player);
}

int IntroLevel::init(Player* p1) {
	player = p1;

	playerSpawn = sf::Vector2f(110.f, 100.f);
	

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
	read_ints("Assets/Levels/MapFiles/Intro_Logic.csv", logicGrid2);
	int* tileTypes1 = new int[1024];
	read_ints("Assets/Levels/MapFiles/Intro_Layer1.csv", tileTypes1);
	int* tileTypes2 = new int[1024];
	read_ints("assets/Levels/MapFiles/Intro_Layer2.csv", tileTypes2);
	int* tileTypes3 = new int[1024];
	read_ints("assets/Levels/MapFiles/Intro_Layer3.csv", tileTypes3);

	sf::Vector2i mapDimChunks1(2, 2);

	tileMap = new TileMap(tileTypes1, tileTypes2, tileTypes3, logicGrid2,
		mapDimChunks1, terrain1, terrain2, rocks);

	tileMap->texDim1 = sf::IntRect(1, 1, 25, 38);
	tileMap->offsetDim1 = sf::Vector2i(10, 16);
	tileMap->texDim2 = sf::IntRect(26, 1, 25, 38);
	tileMap->offsetDim2 = sf::Vector2i(10, 16);
	tileMap->texDim3 = sf::IntRect(54, 0, 21, 33);
	tileMap->offsetDim3 = sf::Vector2i(5, 13);

	if (!shader.loadFromFile("Shaders/test6.frag", sf::Shader::Fragment))
		return -1;
	usingShader = true;

	sf::Vector2i mapPixelDim(tileMap->getMapDimTiles().x * tileMap->tileSize,
		tileMap->getMapDimTiles().y * tileMap->tileSize);

	mapMaskTex.create(mapPixelDim.x, mapPixelDim.y);
	mapMask.setTexture(mapMaskTex);
	shader.setUniform("u_resolution", sf::Vector2f(mapPixelDim.y, mapPixelDim.y));
	shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
	shader.setUniform("radius", 1.f);

	if (!tileMap->bgTex.loadFromFile("Textures/black.png"))
		return -1;

	tileMap->init();
	tileMap->updatePlayerChunk(player->getPosition());
	tileMap->updateTexMap();

	return 0;
}