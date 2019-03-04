#include "Button.hpp"

Button::Button(std::string displayText, sf::Vector2f location, 
	sf::Vector2f buttonSize, const sf::Color & color, int fontSize, int newBid): 
	currentText(displayText, sf::Vector2f(location.x + buttonSize.x / 6,
		location.y - buttonSize.y / 10), sf::Color::White, fontSize, 
		"fonts/Xpressive Regular.ttf" )
{
	buttonId = newBid;
    buttonShape.setPosition(location.x, location.y);
    buttonShape.setSize(buttonSize);
    buttonShape.setFillColor(color);
    buttonShape.setOutlineThickness(-1);
    buttonShape.setOutlineColor(sf::Color::White);
    currentState = false;

}
Button::Button(const Button & b): 	
	currentText(b.currentText.getString(), b.currentText.getPosition(), 
		sf::Color::White, 48, "fonts/Xpressive Regular.ttf" )
{
	buttonId = b.buttonId;
    buttonShape.setPosition(b.buttonShape.getPosition().x, 
    	b.buttonShape.getPosition().y);
    buttonShape.setSize(b.buttonShape.getSize());
    buttonShape.setFillColor(b.buttonShape.getFillColor());
    buttonShape.setOutlineThickness(-1);
    buttonShape.setOutlineColor(sf::Color::White);
    currentState = false;

}

void Button::shiftTextInside(sf::Vector2f & shift) {
	currentText.setPosition(shift);
}

void Button::setColor(const sf::Color & color) {
	buttonShape.setFillColor(color);
}
void Button::setText(std::string displayText) {
	currentText.setString(displayText);
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

