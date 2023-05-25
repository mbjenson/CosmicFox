#pragma once
#include <SFML/Graphics.hpp>
#include "MappingFunctions.h"

// to animate tiles, we will take a pointer to an array of tiles. then, each time we update the mapTex we can
// go into the array of isAnimated tiles and update each one,
class TileMap
{
public:

	/*
	creates a new tileMap
	*/
	TileMap(int* types1, int* types2, int* types3, int* _logic, sf::Vector2i _mapDimChunks, sf::Texture* layer1, sf::Texture* layer2, sf::Texture* layer3);
	//TileMapmk2(sf::Vector2i _mapDimChunks, sf::Texture* layer1, sf::Texture* layer2);
	
	//Initializes the sf::renderTexture mapTex.
	
	void init();		

	/*
	loops through the animatedTiles array and updates each of those tiles animations 1 frame over.
	I will have a universal tick rate that updates the animated tiles in the tilemap.
	and the animated tiles will be drawn on top of their old selves when this runs.
	*/
	void updateAnimations();

	/*
	Loops through the *tileTypes array and grab the texture from the corresponding array
	of actual tiles. This texture is drawn onto the renderTexture. This render texture is static and allows
	for very fast loading of the game.
	*/
	void updateTexMap();
	//void updateTexMap(sf::IntRect drawArea);
		
	/*
	Checks for the players coordinates to see if they have left the current chunk.
	If they have, sets the current chunk that the player is within the map. 
	*/
	bool checkForUpdate(sf::Vector2f playerPos);
	/*
	Perhaps a draw function for an 'Animated Layer' of tiles
	*/
	// naught
	
	void updateBG(sf::Vector2f cameraCenter);
	
	// updates the player's current chunk
	void updatePlayerChunk(sf::Vector2f playerPos);

	// get curChunk
	sf::Vector2i getPlayerChunk();

	// returns the tile logic specified in the logicGrid given a player's position
	int getTileLogic(sf::Vector2f playerPos);

	// gets the tileType at a given location
	int getLayer1TypeAt(int x, int y);

	// get mapTex
	sf::RenderTexture* getMapTex();

	// get mapDimensions in tiles
	sf::Vector2i getMapDimTiles();

	// get tileSize
	int getTileSize();

	// get a tile's top left corner position with floating point coordinates
	sf::Vector2f getTilePos(sf::Vector2f coords);

	// get a which tile coords are located
	sf::Vector2i getTileWithCoords(sf::Vector2f coords);

	sf::Vector2f bgOffset = sf::Vector2f(0.f, 0.f);

	int* layer1Types;
	int* layer2Types;
	int* layer3Types;

	int* logicGrid;

	sf::RenderTexture mapTex; // we will draw the textures for the tile map to this texture;

	int tileSize = 16; // num pixels per tile where (x = tileSize, y = tileSize)
	int chunkSize = 16; // num tiles per chunk where (x = chunkSize, y = chunkSize)

	sf::Vector2i curChunk; // the player's current chuck in the world.
	sf::Vector2i mapDimChunks; // the dimensions of the world in chunks.

	sf::Texture* layer1Texture;
	sf::Texture* layer2Texture;
	sf::Texture* layer3Texture;

	sf::Texture bgTex;
	sf::Sprite bg;

	sf::IntRect curDrawArea;

	// the different texture dimensions for the non-square textures that will be rendered.
	sf::IntRect texDim1;
	sf::Vector2i offsetDim1;

	sf::IntRect texDim2;
	sf::Vector2i offsetDim2;

	sf::IntRect texDim3;
	sf::Vector2i offsetDim3;

	sf::IntRect texDim4;
	sf::Vector2i offsetDim4;

	sf::IntRect texDim5;
	sf::Vector2i offsetDim5;

	sf::IntRect texDim6;
	sf::Vector2i offsetDim6;

};

