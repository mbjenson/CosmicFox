#pragma once
#include "SFML/Graphics.hpp"

// -> the inline keyword is used when you want to define a function that will be inherited to more than one file

// convert screen coordinates to world coordinates
inline sf::Vector2f screenToWorld(float x, float y, sf::Vector2f viewTopLeft) {
	return(sf::Vector2f(x + viewTopLeft.x, y + viewTopLeft.y));
}
// convert world coordinates to screeen coordinates
inline sf::Vector2f worldToScreen(float x, float y, sf::Vector2f viewTopLeft) {
	return(sf::Vector2f(x - viewTopLeft.x, y + viewTopLeft.y));
}
// convert world coordinates to section coordinates
inline sf::Vector2i worldToSection(float x, float y, int sectionSize) {
	return(sf::Vector2i(static_cast<int>(x) / sectionSize, static_cast<int>(y) / sectionSize));
}

inline int cordsToIndex(int x, int y, sf::Vector2i dimensions) {
	return(x + y * dimensions.x);
}