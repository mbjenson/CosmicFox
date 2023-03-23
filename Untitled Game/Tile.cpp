#include "Tile.h"

//NOTE: write collision checking function in the main.cpp file. takes pointer to both a player and a tilemap
//NOTE: the collision detection function will check each of the 8 surrounding tiles
//		1) isCollidable = true
//			then compare the bounds and adjust the allowed movement accordingly
//		2) isCollidable = false
//			then do nothing and act natural

//NOTE: dont need to include the texture in the sprite thing because when we give it the texture
//		we can adjust the int rect to change for animation etc....

//constructor



Tile::Tile(sf::Texture& _texture, bool isCollidable,
	int rowLength, int rowNumber, float animationTime) :
	Animation(_texture, sf::Vector2u(16, 16), rowLength, rowNumber, animationTime)
{
	collidable = isCollidable;
};

Tile::Tile(sf::Texture& _texture, sf::Vector2u _textureDim, bool isCollidable,
	int rowLength, int rowNumber, float animationTime) :
	Animation(_texture, _textureDim, rowLength, rowNumber, animationTime)
{
	collidable = isCollidable;
}

// simplified version (Use this for tiles)
Tile::Tile(sf::Texture& _texture, sf::Vector2u _textureDim, int rowNumber)
	: Animation(_texture, _textureDim, rowNumber) {}

//default constrctor. Later supply the position of the tile. for now the tile will be without position

Tile::Tile() {};
//destructor
Tile::~Tile() {};