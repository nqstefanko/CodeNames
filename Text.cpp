#include "Text.hpp"

Text::Text(std::string displayText, sf::Vector2f location, const sf::Color & color,
	int fontSize, std::string fontFile)
{
	setTextItems(displayText, location, color, fontSize, fontFile);
}

void Text::setTextItems(std::string displayText, sf::Vector2f location, 
	const sf::Color & color, int fontSize, std::string fontFile) {
	if (!font.loadFromFile(fontFile))
	{
	    std::cout << "Unable to Load Font" << std::endl;
	}
	theText = displayText;
	currentText.setFont(font); // font is a sf::Font
	currentText.setString(displayText);
	currentText.setPosition(location.x,location.y);
	currentText.setCharacterSize(fontSize); // in pixels, not points!
	currentText.setFillColor(color);	
}

const sf::Vector2f & Text::getPosition() const {
	return 	currentText.getPosition();
}

void Text::setPosition(const sf::Vector2f & shift) {
	currentText.setPosition(shift);
}

const sf::Vector2f & Text::getPosition() {
	return currentText.getPosition();
}
const sf::FloatRect Text::getGlobalBounds() {
	return currentText.getGlobalBounds();
}

std::string Text::getString() const {
	return theText;
}

void Text::setColor(sf::Color c) {
	return currentText.setFillColor(c);
}

void Text::setString(std::string s) {
	currentText.setString(s);
}

void Text::draw(sf::RenderWindow & window) {
	window.draw(currentText);
}



// Text::Text(){
// 	if (!Text::font.loadFromFile(FONTF))
// 	{
// 	    std::cout << "Unable to Load Font" << std::endl;
// 	}

// 	currentText.setFont(font); // font is a sf::Font
// 	currentText.setString("");
// 	currentText.setFillColor(sf::Color::White); // in pixels, not points!

// }
