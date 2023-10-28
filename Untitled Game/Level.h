#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "ResHandler.h"


/*
 * Generic level class that implemented levels inherit 
 * contains the tilemap, sounds, enemies, textures, player, and all things that go into making a level
*/
class Level 
{
public:
	/*
	* Renders a level to the window
	* uses the player position and screen size to determine the render distance
	* parses the submaps into chunks to only render necessary sprites to the screen to save time and reduce draw calls
	*/
	void render(sf::RenderWindow& win);
	/*
	* updates all enemies present in the level
	*/
	void updateEnemies(float deltaTime, sf::RenderWindow* window);

	// contains grid of textures in three levels
	TileMap* tileMap;
	
	Player* player; // get needed infomation about player status for tileMap
	sf::Shader levelShader;
	
	std::vector<Enemy> eVec; // enemies
	float enemyRenderDistance = 300.f;
	float enemyPlayerCollisionCheckDistance = 40.f;
	sf::Vector2f playerSpawn;
	sf::Shader shader;
	bool usingShader;
	sf::Texture mapMaskTex;
	sf::Sprite mapMask;

	sf::SoundBuffer sBuf;
	sf::Sound s1;
	sf::Sound s2;
	sf::Sound s3;

	bool hasEnemies;
	int numEnemies = 0;
};

