#pragma once
#include <SFML/Graphics.hpp>

//basically a struct for placing the specific info about an animation
class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation();
	~Animation();
	Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime);
	Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowNumber);

	void updateAnimation(sf::Clock* clock);
	void updateAnimation();
	void updateRow(int rowNum, int rowLength);
	void updateAnim();
	
	sf::Clock animTimer;
	float animTime;
	sf::Sprite tSprite;
	int rowLen;
	int rowNum;
	sf::Vector2u tDim;
	sf::IntRect texRect;
	
	// add bounds floatrect and init it in tilemap, and player files. this way we can access the bounding box
	//	for the player but we dont have to use the sprite information. (using sprite information messed up the whole thing idk why)

	// this can be removed by simpy replacing its references in update animation to simply use getTextureRect instead
	
	

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(tSprite, states);
	}
};
