#ifndef BUTTON
#define BUTTON

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Text.hpp"
#include "Util.hpp"

class Button
{
public:
	int buttonId;
	bool one;
	bool two;
	Button(std::string displayText, sf::Vector2f location, sf::Vector2f size,
		const sf::Color & color, int fontSize, int newBid);
	Button(const Button & b);
	void setColor(const sf::Color & color);
	void setText(std::string displayText);

	bool checkClick (sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);
	void drawTimerTokens(sf::RenderWindow & window);

	void shiftTextInside(sf::Vector2f & shift);//, sf::RenderWindow & window);
	const sf::Vector2f & getPosition();

private:
	sf::RectangleShape buttonShape;
	sf::RectangleShape playerOneTimerToken;
	sf::RectangleShape playerTwoTimerToken;

	Text currentText;
	bool currentState;

};

#endif