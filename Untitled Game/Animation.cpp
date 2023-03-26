#include "Animation.h"

//def constructor
Animation::Animation() {};

//constructor
Animation::Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime) {
	// set texture sheet
	tSprite.setTexture(textureSheet);
	// set default animation position with give row number
	tSprite.setTextureRect(sf::IntRect(0, rowNumber * textureDim.y, textureDim.x, textureDim.y));
	//init fields from provided information
	texRect = tSprite.getTextureRect();
	animTime = animationTime;
	rowNum = rowNumber;
	rowLen = rowLength;
	tDim = textureDim;
}

Animation::Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowNumber) {
	tSprite.setTexture(textureSheet);
	tSprite.setTextureRect(sf::IntRect(0, rowNumber * textureDim.y, textureDim.x, textureDim.y));
	animTime = 0.f;
	rowNum = rowNumber;
	rowLen = 1;
	tDim = textureDim;
}


//deconstructor
Animation::~Animation() {};

void Animation::updateAnimation() {
	if (animTime > 0) {
		if (texRect.left == tDim.x * (rowLen - 1)) {
			//return to beginning of texture frame
			texRect.left = 0;
		}
		// if not at end of row
		else {
			//move to next texture frame
			texRect.left += tDim.x;
		}
	}
}

void Animation::updateAnim() {
	int curTime = animTimer.getElapsedTime().asMilliseconds();
	// making sure that thing is animated
	if (animTime > 0) {
		if (curTime > animTime) {
			animTimer.restart();
			if (texRect.left >= tDim.x * (rowLen - 1))
				texRect.left = 0;
			else
				texRect.left += tDim.x;
		}
		tSprite.setTextureRect(texRect);
	}
}

void Animation::updateAnimation(sf::Clock* clock)
{
	if (animTime != 0)
	{
		if (clock->getElapsedTime().asSeconds() > animTime)
		{
			// check if at end of row
			clock->restart();
			if (texRect.left >= tDim.x * (rowLen-1))
			{
				//return to beginning of texture frame
				texRect.left = 0;
			}
			// if not at end of row
			else
			{
				//move to next texture frame
				texRect.left += tDim.x;
			}
		}
		tSprite.setTextureRect(texRect);
	}
}

void Animation::updateRow(int rowNumber, int rowLength)
{
	texRect.top = rowNumber * tDim.y;
	tSprite.setTextureRect(texRect);
	rowNum = rowNumber;
	rowLen = rowLength;
}




