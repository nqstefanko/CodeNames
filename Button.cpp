#include "Button.hpp"

Button::Button(std::string displayText, sf::Vector2f location, sf::Vector2f buttonSize,
	 const sf::Color & color, int fontSize, int newBid): 
		currentText(displayText, sf::Vector2f(location.x+buttonSize.x/6,location.y-buttonSize.y/10),
			sf::Color::Black,fontSize, "fonts/Xpressive Regular.ttf" )
{
	buttonId = newBid;
    buttonShape.setPosition(location.x,location.y);
    buttonShape.setSize(buttonSize);
    buttonShape.setFillColor(color);
	
    currentState = false;

}

void Button::shiftTextInside(sf::Vector2f &shift, sf::RenderWindow &window) {
	currentText.setPosition(shift);
	currentText.draw(window);
}


void Button::draw(sf::RenderWindow &window) {
	//std::cout << "Drawing Button" << std::endl;
	window.draw(buttonShape);
	currentText.draw(window);
}

bool Button::checkClick (sf::RenderWindow &window, ButtonActions &actions) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos= sf::Mouse::getPosition(window);
		sf::Vector2f currMousePosF(mousePos.x,mousePos.y);
		if(buttonShape.getGlobalBounds().contains(currMousePosF)) {
			actions.key_pressed(buttonId, window);//Do associated action with button
			return true;
		}
	}
	return false;
}

//Inits the obj, then initsilaies.


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