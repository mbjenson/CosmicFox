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

### TileMap
- The Tilemap uses a chunk and grid based system.
- the two layers are like the floor and the carpet. These layers contain the ground tile type and any overlay like grass that would appear on top of it.
#### > Rendering and Optimizations
- The bottom two layers of the tilemap are drawn to a render texture that acts as a single sprite and can be displayed every frame with one draw instruction and updates only when the player enters a new chunk. This method of drawing to a render texture greatly increased performance and allowed for seamless transition between chunks as the player moves about the level.

### Levels
- The level class contains things like sounds, background images, a tilemap, enemy data, and more.
- It is the base class for the levels in the game.
- levels, like tilemaps, uses a grid and chunk system.
#### > Rendering and optimization
- The level renders by drawing the background, the tilemap, and then drawing an interactive layer of objects. the interactive layer of objects contains stones, trees, and other objects the player can move around.
- To make it appear as though the player is moving behind objects in the level, the player is drawn at the end of its respective row position, so after a row of interactable trees or stone is drawn, the current row being drawn is checked against the players row and the player is drawn if they match.
- The entities are also drawn in this fasion.
### shaders
#### GLSL shader use
- shaders in this game were written using GLSL.
- The second level in cosmic fox includes a shaders which is used illuminate the area around the player.
- A dark mask is drawn over the whole level and the shader, given the player's world position, uses linear interpolation to generate a smoothly faded circle of underdarkened area around the player.

### 
### talk about the algorithms you made for collisions, drawing and what not. Chunk loading and culling.
### 

## Art
## art style
### tile
- All of the art for this game was creted using GIMP. (GNU image manipulation program).

### music









