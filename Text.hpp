#ifndef MY_TEXT
#define MY_TEXT

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <stdlib.h>

class Text
{
public:
	Text();
	Text(std::string displayText, sf::Vector2f location, const sf::Color & color, int fontSize, std::string fontFile);
	void draw(sf::RenderWindow &window);
	void setPosition(const sf::Vector2f& shift);


private:
	sf::Font font;
	sf::Text currentText;

};

#endif