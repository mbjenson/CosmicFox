#pragma once
#include <SFML/Graphics.hpp>

// Base class for animated objects.
class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation();
	~Animation();
	Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowLength, int rowNumber, float animationTime);
	Animation(sf::Texture& textureSheet, sf::Vector2u textureDim, int rowNumber);
	
	void updateAnimation();
	void updateRow(int rowNum, int rowLength);
	void updateAnim();
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
