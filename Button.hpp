#ifndef BUTTON
#define BUTTON

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "ButtonActions.hpp"
#include "Text.hpp"

class Button
{
public:
	int buttonId;
	Button(std::string displayText, sf::Vector2f location, sf::Vector2f size,
		const sf::Color & color, int fontSize, int newBid);
	void setColor(const sf::Color & color);
	bool checkClick (sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);
	void shiftTextInside(sf::Vector2f & shift, sf::RenderWindow & window);

private:
	sf::RectangleShape buttonShape;
	Text currentText;
	bool currentState;

};

#endif