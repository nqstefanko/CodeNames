#ifndef BUTTON
#define BUTTON

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "ButtonActions.hpp"

class Button
{
public:
	int buttonId;
	Button(std::string displayText, sf::Vector2f location, sf::Vector2f size,
		const sf::Color & color, int fontSize, int newBid);
	void checkClick (sf::RenderWindow &window, ButtonActions &actions);
	void draw(sf::RenderWindow &window);

private:
	sf::RectangleShape buttonShape;
	sf::Font font;
	sf::Text currentText;
	bool currentState;

};

#endif