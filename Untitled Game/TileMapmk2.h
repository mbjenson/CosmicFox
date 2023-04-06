#pragma once
#include <SFML/Graphics.hpp>
#include "MappingFunctions.h"
#include "Tile.h"

// to animate tiles, we will take a pointer to an array of tiles. then, each time we update the mapTex we can
// go into the array of isAnimated tiles and update each one,
class TileMapmk2
{
public:

	/*
	creates a new tileMap
	*/
	TileMapmk2(int* types1, int* types2, int* _logic, sf::Vector2i _mapDimChunks, sf::Texture* layer1, sf::Texture* layer2);
	//TileMapmk2(sf::Vector2i _mapDimChunks, sf::Texture* layer1, sf::Texture* layer2);
	/*
	Initializes the sf::renderTexture mapTex.
	MAYBE: will initialize the animated tiles for the map.
		Loops through the array of ints which represents the tile types and if the tile type (an int)
		Matches one of those that are said to be animated, the tile coord value for this tile is added to
		the animatedTile array.
	*/
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

	/*
	Checks for the players coordinates to see if they have left the current chunk.
	If they have, sets the current chunk that the player is within the map. 
	*/
	bool check(sf::Vector2f playerPos);
	
	// updates the player's current chunk
	void updatePlayerChunk(sf::Vector2f playerPos);

	// get curChunk
	sf::Vector2i getPlayerChunk();

	// returns the tile logic specified in the logicGrid given a player's position
	int getTileLogic(sf::Vector2f playerPos);

	// gets the tileType at a given location
	int getTileTypeAt(int x, int y);

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

private:

	int* layer1Types;
	int* layer2Types;
	int* logicGrid;
	sf::RenderTexture mapTex; // we will draw the textures for the tile map to this texture;
	int tileSize = 16; // num pixels per tile where (x = tileSize, y = tileSize)
	int chunkSize = 16; // num tiles per chunk where (x = chunkSize, y = chunkSize)
	sf::Vector2i curChunk; // the player's current chuck in the world.
	sf::Vector2i mapDimChunks; // the dimensions of the world in chunks.
	sf::Texture* layer1Texture;
	sf::Texture* layer2Texture;
	//sf::Texture* layer3Texture;
};

