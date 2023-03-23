#pragma once
#include <SFML/graphics.hpp>
#include "Tile.h"
/*

provide function that can render a certain number of tiles around the player.

* Contains map of tiles in a grid
* Contains a logical grid that has collisions for static objects
* 
* NOTE: tiles will render at a certain region around the player as to reduce graphical load.	
* 
*/




class TileMap : private Tile
{
public:
	TileMap();

	TileMap(sf::Vector2i _mapSize, int* _tileTypes, int* _logGrid,
			sf::Texture& textureSheet, sf::Vector2u _tileSize);

	TileMap(int numTileTypes, Tile* _tilesArr, sf::Vector2i _mapSize, int* _tileTypes, int* _logGrid, sf::Vector2u _tileSize);

	~TileMap();

	void render(sf::Vector2i curTile, sf::RenderWindow& win, sf::Vector2i _rendSize);
	void renderAll(sf::RenderWindow& win);
	// whichRow is the coordinate of the row
	//		if i want a row two above i input -2
	void renderRow(sf::Vector2i curTile, int whichRow, sf::Vector2i, sf::RenderWindow& win);
	void renderOne(sf::RenderWindow& win, int x, int y);

	sf::Vector2u tileSize;
	//visual grid
	std::vector<Tile> tileV;
	//logic grid
	
	sf::Vector2i mapSize;

	Tile getTileAt(int x, int y);
	Tile getTileWithPoints(sf::Vector2f cords);

private:

	int* tileTypes;	
	sf::Texture texSheet;
	Tile* tilesArr;
	int numTileTypes;

};



	/*
	functionality:
		create a tilemap:
			The tilemap will be a vector of tiles, each containing details about collisions,
			textures, animations, lighting, etc...
			The tile map would need to take a pointer to an array of integers that 
			specify which types of tile we will use at each spot.
			
			
	  
		load a portion of the tilemap to screen (draw):
			To load an entire tilemap is not good practice and results in stress on the gpu.
			A solution to this is to only render a certain area of a designated size around the player.
			
			Method 1)
					Use the deconstructor for the tile class to deconstruct any tiles that are no
					long in range of the player. Find the indecies that are within the range of the
					player and create new Tile obects (if necessary) and render them to screen.
					Here we must also load the logic map to the screen, the same way wed render the tiles
			
			Method 2)
					Assuming the tilemap is small enough, we can load everything into memory and only
					draw the parts of the map that are visible to the player like we would above.
					This is easier but requires more gpu stress. This means that every tile,
					along with its animation/static texture, collision, vertex array, etc, will be
					loaded into memory and only certain parts of it will be draw.
		
			Method 3)
					This method is a combination of the first two. Here we will load a larger area into
					memory, and access the things inside of that area which would be faster because
					we wouldn't have deconstruct and construct so many tiles. It would be moderately efficient
					in gpu usage.
	
	*/
	



