# CosmicFox
Cosmic Fox is a Top-down 2D action zelda-like game.

<img width="600" alt="image" src="https://github.com/mbjenson/CosmicFox/blob/master/CosmicFoxTitle.png">

*A space-faring forest animal has found himself stranded on a strange planet of floatting islands and must protect himself and his luminescent companion from the mysterious threats that lurk above the clouds.*

## *note to reader:*
Being that this was one of my first larger-scale projects, it contains some good, it also contains some sloppy code. That being said, this project mainly served as a foundational learning experience in my programming, problems solving, and creative journey that I can credit with many of my biggest lessons in the dos and donts of software development.

## Build
...

## Purpose
The main purpose of this project was to create a game with no pre-existing engine and study the underlying structure and principles of games and their development process while building my programming, organization, and problem solving skills.

## Gameplay features
- Top-down 2D.
- Level progression through 3 completed maps.
- Dashing and sword combat.
- retro-pixel art style (all original artwork).
- Orchestral Music.

## Previews

### Demo Video:
#### https://youtu.be/BHPyVc5tPnQ

### Environments:
#### *Crash Site:*
![](https://github.com/mbjenson/CosmicFox/blob/master/crashSite.png)
#### *Mountain Pass:*
![](https://github.com/mbjenson/CosmicFox/blob/master/MountainPassCosmicFox.png)
#### *Bridge:*
![](https://github.com/mbjenson/CosmicFox/blob/master/bridgeCosmicFox.png)
#### *Grass Lands:*
![](https://github.com/mbjenson/CosmicFox/blob/master/GrassLandsCosmicFox1.png)




## Implementation
### C++ Use
The entire project is coded in C++. The IDE used was Visual Studio 2019

## World
- This game uses a tile based system for the world. 

### TileMap
- The Tilemap uses a chunk and grid system to manage placement/loading of the map.
- The information for the map's data is stored in csv files. The csv files are read into memory when the corresponding level is loaded into the game.
- The tilemap is made up of three layers of tiles.
#### Rendering and Optimization
- Each tile is dynamically drawn to a single texture which is drawn using a single draw call. It updates only when the player enters a new chunk. This greatly increased performance and allowed for seamless transition around the level.
- The Level is culled at a set distance to only load the part of the world the player can see.

### Levels
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
- A Custom algorithm for collision detection and resolution was created and used
- 8 cases are considered when evaluating collisions.
- Collidable objects have rectangular bounding boxes.

## Animation
- the animation class provides basic functionality for animating objects using spritesheets.

## Player.cpp
- The player class controls all the players interactions with the world, user input, and more.
- the file contains just around 800 lines of code that handle everything from collision detection and sword mechanics to animation logic and sound.
- the update function handles the logic and flow of the players state. An enum class was used to handle the different player states and designate distinct sections of logic in the function.

## Enemies
- The enemy in this game is an undead fox-like creature.
- The enemy ai uses different pursuit and dash mechanics that make for high-intensity gameplay.

## Art
- All of the art for this game is original and was creted using GIMP. (GNU image manipulation program).
A retro-pixel art style was chosen for this game.

## music
- Music for this game was written using REAPER digital audio workspace and the BBC symphony orchestra core from Spitfire Audio.






