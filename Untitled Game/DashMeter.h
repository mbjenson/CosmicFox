#pragma once
#include <SFML/graphics.hpp>

/*
* player hud element.
* Displays the players dash cooldown meter.
*/
class DashMeter
{
public:
	DashMeter() {
		meter.setFillColor(sf::Color(130, 25, 45, 190));
	}

	void render(sf::RenderWindow& win, int dashClock, sf::Vector2f topLeftCorner) {
		if (dashClock > 1400) {
			meter.setSize(sf::Vector2f(1400.f / ratio, 8.f));
			meter.setFillColor(ready);
		}
		else {
			meter.setSize(sf::Vector2f(float(dashClock) / ratio, 8.f));
			meter.setFillColor(loading);
		}
		meter.setPosition(topLeftCorner.x + 50.f, topLeftCorner.y + 6.f);
		win.draw(meter);
	}

	sf::RectangleShape meter;
	float ratio = 50.f;
	sf::Color loading = sf::Color(130, 25, 45, 190);
	sf::Color ready = sf::Color(15, 130, 45, 190);
};

