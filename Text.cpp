#include "Text.hpp"

Text::Text(std::string displayText, sf::Vector2f location, const sf::Color & color, int fontSize, std::string fontFile)
{
	if (!font.loadFromFile(fontFile))
	{
	    std::cout << "Unable to Load Font" << std::endl;
	}

	currentText.setFont(font); // font is a sf::Font
	currentText.setString(displayText);
	currentText.setPosition(location.x,location.y);
	currentText.setCharacterSize(fontSize); // in pixels, not points!
	//currentText.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
}

void Text::draw(sf::RenderWindow &window) {
	window.draw(currentText);
}