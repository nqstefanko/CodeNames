#include "Button.hpp"

Button::Button(std::string displayText, sf::Vector2f location, 
	sf::Vector2f buttonSize, const sf::Color & color, int fontSize, int newBid): 
	
	currentText(displayText, sf::Vector2f(location.x + buttonSize.x / 6,
		location.y - buttonSize.y / 10), sf::Color::Black, fontSize, 
		"fonts/Xpressive Regular.ttf" )
{
	buttonId = newBid;
    buttonShape.setPosition(location.x, location.y);
    buttonShape.setSize(buttonSize);
    buttonShape.setFillColor(color);
    currentState = false;

}

void Button::shiftTextInside(sf::Vector2f & shift, sf::RenderWindow & window) {
	currentText.setPosition(shift);
	currentText.draw(window);
}


void Button::draw(sf::RenderWindow & window) {
	window.draw(buttonShape);
	currentText.draw(window);
}

bool Button::checkClick (sf::RenderWindow & window) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f currMousePosF(mousePos.x, mousePos.y);
		if(buttonShape.getGlobalBounds().contains(currMousePosF)) {
			return true;
		}
	}
	return false;
}

