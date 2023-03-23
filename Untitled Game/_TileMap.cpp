#include "_TileMap.h"

bool _TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
	if (!m_tileset.loadFromFile(tileset))
		return false;
	
	//reside the vertex array to fit the level size specified in the params
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	//populate th evertex array, with one quad per tile
	for (unsigned int i = 0; i < width; i++) 
	{
		for (unsigned int j = 0; j < height; j++)
		{
			// tiles eg.
			// const int * tiles = [0, 1, 1, 0
			//						1, 2, 1, 0
			//						1, 4, 2, 1
			//						0, 0, 1, 2]
			// this goes through and gets the number at that spot then from there
			//		it uses that number as a coordinate for the texture in the texture file

			//get the current tile number
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			//get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			//definte its 4 corner
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
	return true;
}
/*
//=======
const int level[] =
{
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3,
	0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
	0, 1, 1, 0, 3, 3, 3, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 1, 1, 1, 1, 1, 1, 2, 0, 0,
	0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
	2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3,
	0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
	0, 1, 1, 0, 3, 3, 3, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 1, 1, 1, 1, 1, 1, 2, 0, 0,
	0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
	2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
};

_TileMap map;
if (!map.load("Textures/graphics-vertex-array-tilemap-tileset.png", sf::Vector2u(32, 32), level, 32, 16))
return -1;
//=======
*/