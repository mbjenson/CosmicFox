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
	TileMapmk2(Tile* _tiles, int* _types, int* _logic);

	/*
	Initializes the sf::renderTexture mapTex.
	will initialize the animated tiles for the map.
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
	void updateDraw(sf::RenderWindow& win);

	/*
	Checks for the players coordinates to see if they have left the current chunk.
	If they have, sets the current chunk that the player is within the map. 
	*/
	void check();
	
	// updates the player's current chunk
	void updatePlayerChunk(sf::Vector2f playerPos);
	// Returns curChunk
	sf::Vector2i getPlayerChunk();

private:

	Tile* tiles;
	int* tileTypes;
	int* logicGrid;
	sf::RenderTexture mapTex; // we will draw the textures for the tile map to this texture;
	int tileSize = 16; // num pixels per tile where (x = tileSize, y = tileSize)
	int chunkSize = 8; // num tiles per chunk where (x = chunkSize, y = chunkSize)
	sf::Vector2i curChunk; // the player's current chuck in the world.
	sf::Vector2i mapDimChunks; // the dimensions of the world in chunks.
};

