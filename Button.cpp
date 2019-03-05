#include "Button.hpp"

Button::Button(std::string displayText, sf::Vector2f location, 
	sf::Vector2f buttonSize, const sf::Color & color, int fontSize, int newBid): 
	currentText(displayText, sf::Vector2f(location.x + buttonSize.x / 6,
		location.y - buttonSize.y / 10), sf::Color::White, fontSize, 
		FONTF )
{
	buttonId = newBid;
    buttonShape.setPosition(location.x, location.y);
    buttonShape.setSize(buttonSize);
    buttonShape.setFillColor(color);
    buttonShape.setOutlineThickness(-1);
    buttonShape.setOutlineColor(sf::Color::White);
    
    sf::Vector2f tokenSize(buttonSize.x/5, buttonSize.y/4);
    playerOneTimerToken.setSize(tokenSize);
    playerOneTimerToken.setPosition(location.x+tokenSize.x*3, location.y);
	playerOneTimerToken.setFillColor(sf::Color::Blue);
    playerOneTimerToken.setOutlineThickness(-1);
    playerOneTimerToken.setOutlineColor(sf::Color::White);


    playerTwoTimerToken.setSize(tokenSize);
    playerTwoTimerToken.setPosition(location.x+tokenSize.x*4, location.y);
	playerTwoTimerToken.setFillColor(sf::Color::Red);
    playerTwoTimerToken.setOutlineThickness(-1);
    playerTwoTimerToken.setOutlineColor(sf::Color::White);

    currentState = false;
}

Button::Button(const Button & b): 	
	currentText(b.currentText.getString(), b.currentText.getPosition(), 
		sf::Color::White, 48, FONTF )
{
	buttonId = b.buttonId;
    buttonShape.setPosition(b.buttonShape.getPosition().x, 
    	b.buttonShape.getPosition().y);
    buttonShape.setSize(b.buttonShape.getSize());
    buttonShape.setFillColor(b.buttonShape.getFillColor());
    buttonShape.setOutlineThickness(-1);
    buttonShape.setOutlineColor(sf::Color::White);

    sf::Vector2f tokenSize(b.buttonShape.getSize().x/5, b.buttonShape.getSize().y/3);
    playerOneTimerToken.setSize(tokenSize);
    playerOneTimerToken.setPosition(b.buttonShape.getPosition().x+tokenSize.x*3,
    	b.buttonShape.getPosition().y);
	playerOneTimerToken.setFillColor(sf::Color::Blue);
    playerOneTimerToken.setOutlineThickness(-1);
    playerOneTimerToken.setOutlineColor(sf::Color::White);


    playerTwoTimerToken.setSize(tokenSize);
    playerTwoTimerToken.setPosition(b.buttonShape.getPosition().x+tokenSize.x*4, 
    	b.buttonShape.getPosition().y);
	playerTwoTimerToken.setFillColor(sf::Color::Red);
    playerTwoTimerToken.setOutlineThickness(-1);
    playerTwoTimerToken.setOutlineColor(sf::Color::White);


    one = false;
    two = false;
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

void Button::drawTimerTokens(sf::RenderWindow & window) {
	if(one) {
		window.draw(playerOneTimerToken);
	}
	if(two) {
		window.draw(playerTwoTimerToken);
	}
}

void Button::draw(sf::RenderWindow & window) {
	window.draw(buttonShape);
	drawTimerTokens(window);
	currentText.draw(window);
}

const sf::Vector2f & Button::getPosition() {
	return buttonShape.getPosition();
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

