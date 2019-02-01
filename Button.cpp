#include "Button.hpp"

Button::Button(std::string displayText, sf::Vector2f location, sf::Vector2f buttonSize,
	 const sf::Color & color, int fontSize, int newBid) 
{
	buttonId = newBid;
    buttonShape.setPosition(location.x,location.y);
    buttonShape.setSize(buttonSize);
    buttonShape.setFillColor(color);
	
	if (!font.loadFromFile("fonts/Xpressive Regular.ttf"))
	{
	    std::cout << "Unable to Load Font" << std::endl;
	}

	currentText.setFont(font); // font is a sf::Font
    currentText.setString(displayText);
    currentText.setPosition(location.x+buttonSize.x/6,location.y-buttonSize.y/10);
    currentText.setCharacterSize(fontSize); // in pixels, not points!
	currentText.setStyle(sf::Text::Bold);// | sf::Text::Underlined);

    currentState = false;

}

void Button::draw(sf::RenderWindow &window) {
	std::cout << "Drawing Button" << std::endl;
	window.draw(buttonShape);
	window.draw(currentText);
}

void Button::checkClick (sf::RenderWindow &window, ButtonActions &actions) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos= sf::Mouse::getPosition(window);
		sf::Vector2f currMousePosF(mousePos.x,mousePos.y);
		if(buttonShape.getGlobalBounds().contains(currMousePosF)) {
			actions.key_pressed(buttonId, window);//Do associated action with button
			std::cout << "QUITTING BUTTON" << std::endl;
			window.close();
			exit(0);
		}
	}

}

// void Button::checkClick (sf::RenderWindow &window, void (*fp)()) {
// 	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
// 		sf::Vector2i mousePos= sf::Mouse::getPosition(window);
// 		sf::Vector2f currMousePosF(mousePos.x,mousePos.y);
// 		if(buttonShape.getGlobalBounds().contains(currMousePosF)) {
// 			std::cout << "QUITTING BUTTON" << std::endl;
// 			fp();
// 			//window.close();
// 			//exit(0);
// 		}
// 	}

// }

// double (*f)(double, double)
// sf::Mouse::isButtonPressed(sf::Mouse::Left)