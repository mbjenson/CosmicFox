#pragma once
#include "SFML/Graphics.hpp"

// convert screen coordinates to world coordinates
sf::Vector2f screenToWorld(float x, float y, sf::Vector2f viewTopLeft) {
	return(sf::Vector2f(x + viewTopLeft.x, y + viewTopLeft.y));
}
// convert world coordinates to screeen coordinates
sf::Vector2f worldToScreen(float x, float y, sf::Vector2f viewTopLeft) {
	return(sf::Vector2f(x - viewTopLeft.x, y + viewTopLeft.y));
}
// convert world coordinates to section coordinates
sf::Vector2i worldToSection(float x, float y, int sectionSize) {
	return(sf::Vector2i(static_cast<int>(x) / sectionSize, static_cast<int>(y) / sectionSize));
}