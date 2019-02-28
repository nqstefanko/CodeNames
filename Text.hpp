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
	//Text();
	Text(std::string displayText="", sf::Vector2f location=sf::Vector2f(0,0), const sf::Color & color=sf::Color::White, 
		int fontSize=36, std::string fontFile="fonts/Xpressive Regular.ttf");
	void setTextItems(std::string displayText="", sf::Vector2f location=sf::Vector2f(0,0), const sf::Color & color=sf::Color::White, 
		int fontSize=36, std::string fontFile="fonts/Xpressive Regular.ttf");
	void draw(sf::RenderWindow & window);
	void setPosition(const sf::Vector2f & shift);
	std::string getString() const;
	const sf::Vector2f & getPosition();
	const sf::FloatRect getGlobalBounds();
	void setString(std::string s);

	std::string theText;

private:
	sf::Font font;
	sf::Text currentText;

};

#endif