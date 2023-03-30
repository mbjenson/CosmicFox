#include "Sword.h"

Sword::Sword(sf::Vector2f origin, sf::Texture& texSheet, sf::Vector2u texDim, int rowLen, int rowNum, float animTime) :
	Animation(texSheet, texDim, rowLen, rowNum, animTime)
{
	
}

void Sword::swing(sf::Vector2f dir) {
	// play around with loading things in and out
	// for eg, load in the hitbox for sword, then he rid of it after it is done
	
	// firstly, innit a new hitbox for a given swing
	
	
	// 
}



