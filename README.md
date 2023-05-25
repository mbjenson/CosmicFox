# CosmicFox
A Top-down 2D action zelda-like game with interactive movement and combat.

## Purpose
The main purpose of this project was to create a game with no engine and learn about how rendering works and how games are made.

## Gameplay features
- Top-down 2D.
- Level progression through 3 completed maps.
- Dashing mechanics and sword combat.
- Sword combat.
- Win the game by killing all the undead in the 3rd level.
- player Hud

## game images:
### ***provide a few gifs and images of the games content.

## Implementation
### C++ Use
The entire project is coded in C++. The IDE used was visual Studio 2019

## Tiles
- This game uses a tile based system for the world. 

## TileMap
- The Tilemap uses a chunk and grid based system.
- The information for the map's data is stored in csv files. The csv files are read into memory when the corresponding level is loaded into the game.
- The tilemap is made up of three layers of tiles. the first and second layer are the base layers and act like the floor and rug, so to speak. The third layer is an interactable layer and contains objects which the player can move around.
#### > Rendering and Optimizations
- The bottom two layers of the tilemap are drawn to a render texture that acts as a single sprite and can be displayed every frame with one draw instruction. It updates only when the player enters a new chunk. 
- This method of drawing to a render texture greatly increased performance and allowed for seamless transition between chunks as the player moves about the level.
- An area of 3x3 chunks of the base 2 layers are drawn arouund the player. The interactable layer has a smaller render distance from the player to reduce draw calls and increase performance.

## Levels
- The level class contains things like sounds, background image, a tilemap, enemy data, and more.
- It is the base class for the levels in the game.
- levels, like tilemaps, uses a grid and chunk system.
#### > Rendering and optimization
- The level rendering process starts by drawing the background, the first two layers of the tilemap, then the interactable layer of the tilemap (3rd layer). The 3rd layer is drawn from the the interactive layer of objects contains stones, trees, enemies, and other objects the player can move around.
- To make it appear as though the player is moving behind objects in the level, the player is drawn at the end of its respective row position. In other words, after a row of interactable objects are drawn, the current row being drawn is checked against the players row and the player is drawn if they match.
- Entities are also drawn in this fasion.

## shaders
#### GLSL shader use
- shaders in this game were written using GLSL.
- The second level in cosmic fox includes a shaders which is used illuminate the area around the player.
- A dark mask is drawn over the whole level. The player's world position is calculated and given as a parameter. The shaders linearly interpolates between the black and clear areas to give a smoothly faded edge.

## Collisions
- collidable objects all have a rectangular bounding box. 
- To detect collisions for entities, the algorithm:
1) Gets the location of each corner based on the dimensions of the entities bounding box.
2) Gets the tile coordinates for each corner. each corner has a boolean value. 
3) Looks up those coordinates in the entities current level's tilemap map information array. If that index is a collidable tile, that corners boolean value is set to true.
4) 8 total cases are considered for collision resolution. the cases are for each edge and each corner. the corner cases are resolved by calculating the shortest path to the edge of a collidable tile. this is how the correct direction of resolution is chosen.
6) if a collision is detected, the collision is resolved by subtracting the calculated velocity for the current frame, with the distance the player will overlap with a collidable tile which means the player can never move into a collidable region.
this entire process is repeated only two times. This is because each bounding box is a rectangle and therefore the greatest number of resoltions that will be needed is two.

### 
### talk about the algorithms you made for collisions, drawing and what not. Chunk loading and culling.
### 

## Art
## art style

### tile
- All of the art for this game was creted using GIMP. (GNU image manipulation program).

### music









