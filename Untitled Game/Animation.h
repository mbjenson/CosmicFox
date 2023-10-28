#pragma once
#include <SFML/Graphics.hpp>

/*
* Base class for all animated objects
* 
* Contains functionality for:
*	reading sprite-sheets (image files split into a grid with each being an animated sequence),
*	animating the object, updating which animation is being used, and restarting the animation sequence.
* 
*/
class Animation : public sf::Drawable, public sf::Transformable
{
public:
	
	Animation();
	~Animation();
	Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime);
	Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowNumber);
	
	/*
	* Updates the animation to the next frame
	*/
	void updateAnimation();
	/*
	* Changes which animation (row of images) is being used
	*/
	void updateRow(int rowNum, int rowLength);
	/*
	* Depreciated function; replaced by the above 'updateAnimation'
	*/
	void updateAnim();
	/*
	* restarts an animation sequence by setting the image position to the beginning of the row
	*/
	void restartAnim();
	
	sf::Clock animTimer;
	float animTime;
	sf::Sprite tSprite;
	int rowLen;
	int rowNum;
	sf::Vector2u tDim;
	sf::IntRect texRect;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(tSprite, states);
	}
};
