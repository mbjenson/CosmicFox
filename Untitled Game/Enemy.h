#pragma once

#include "Entity.h"
#include "Sword.h"
#include <SFML/Graphics.hpp>


/*
The enemy in this game will be able to do several different things.
It can move:
	this means it has animation functions.

It can attack:
	It has a sword.







*/

class Enemy : public Entity
{
	Enemy(sf::Texture* spriteSheet);
	Enemy();
	sf::Vector2u animDim;
	int maxHealth;
	int curHealth;
	
	sf::RectangleShape rect;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		/*
		if (attacking) {
			//target.draw(sword.hBox);

			target.draw(sword);
		}
		*/
		//sf::RectangleShape hitBoxdraw(sf::Vector2f(8.f, 6.f));
		//hitBoxdraw.setFillColor(sf::Color::Red);
		//hitBoxdraw.setPosition(sf::Vector2f(hitBox.left, hitBox.top));
		//target.draw(hitBoxdraw);
		target.draw(tSprite, states);
	}
};

