# CosmicFox
Cosmic Fox is a Top-down 2D action zelda-like game with interactive movement and combat and a retro-pixel art style. It was created using the SFML graphics API and Programmed using C++.

<img width="600" alt="image" src="https://github.com/mbjenson/CosmicFox/blob/master/CosmicFoxTitle.png">

*A space-faring forest animal has found himself stranded on a strange planet with floatting islands and must protect himself from the mysterious threats that lurk above the clouds.*

## Purpose
The main purpose of this project was to create a game with no engine and study the underlying structure and principles of games and their development process.

## Gameplay features
- Top-down 2D.
- Level progression through 3 completed maps.
- Dashing mechanics and sword combat.
- retro-pixel art style (all original artwork).
- Orchestral Music.

## Previews

### Environments:
#### Crash Site
![](https://github.com/mbjenson/CosmicFox/blob/master/crashSite.png)
#### Mountain Pass
![](https://github.com/mbjenson/CosmicFox/blob/master/MountainPassCosmicFox.png)
#### Bridge
![](https://github.com/mbjenson/CosmicFox/blob/master/bridgeCosmicFox.png)
#### Grass Lands
![](https://github.com/mbjenson/CosmicFox/blob/master/GrassLandsCosmicFox1.png)

### Demo Video:
### put link here


## Implementation
### C++ Use
The entire project is coded in C++. The IDE used was visual Studio 2019

## Tiles
- This game uses a tile based system for the world. 
- Tiles have textures.

## TileMap
- The Tilemap uses a chunk and grid based system to manage placement/loading of the map.
- The information for the map's data is stored in csv files. The csv files are read into memory when the corresponding level is loaded into the game.
- The tilemap is made up of three layers of tiles.
#### Rendering and Optimization
- Each tile is dynamically drawn to a single texture which is drawn using a single draw call. It updates only when the player enters a new chunk. This greatly increased performance and allowed for seamless transition around the level.
- The Level is culled at a set distance to only load the part of the world the player can see.

## Levels
- The level class contains the Tilemap, sounds, enemies, objectives and other things that make the world interactive.
#### Rendering and Optimization
- The level rendering function is in charge of drawing the tilemap, the player, and the enemies.
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
1) Get corners of player's bounding box.
2) Convert to tile coordinates. each corner has a boolean value assigned to it.
3) Check the tilemap's logic grid to see if it is a collidable tile. set corresponding corner boolean accordingly.
4) 8 total cases are considered for collision resolution. For each edge and each corner.
6) The collision is resolved by subtracting the calculated velocity with the distance the player will overlap a collidable tile. Corner cases are resolved by calculating the shortest path from the player's corner to an edge of the collidable box. 
this entire process is repeated only two times. This is because each bounding box is a rectangle and therefore the greatest number of resoltions that will be needed is two.

## Animation
- the animation class is the class that all moving actors inherit from. This class gives basic functionality for animating objects using spritesheets.

## Player.cpp
- The player class controls all the players interactions with the world, user input, and more.
- the file contains just around 800 lines of code that handle everything from collision detection and sword mechanics to animation logic and sound.
- the update function handles the logic and flow of the players state. An enum class was used to handle the different player states and designate distinct sections of logic in the function.

## Enemies
- The enemy in this game is an undead fox.
- The enemy ai uses a simple pursue and dash sequence that makes for a high action experience.

## Art
All of the art for this game is original and was creted using GIMP. (GNU image manipulation program).
A retro-pixel art style was chosen for this game.

## music
Music for this game was written using REAPER digital audio workspace and the BBC symphony orchestra core from Spitfire Audio.






