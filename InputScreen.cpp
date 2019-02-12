#include "InputScreen.hpp"

InputScreen::InputScreen(std::string & inputString, std::string queryMessage, int maxCharacter)
{
	inputStr = &inputString;
	queryMsg = queryMessage;
	maxChar = maxCharacter;
	initInputComponents();
	initTextComponents();
}


int InputScreen::run(sf::RenderWindow & window) {
	std::string input = "";
	while(window.isOpen()) {
		updateScreen(window);
		updateCursor();
		sf::Event e;
		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) {
				printDebug("Closing Input String");
				window.close();
				return -1;
			} else if (e.type == sf::Event::TextEntered) {
				if(e.text.unicode == 10 || e.text.unicode == 12 || e.text.unicode == 13) {//Ret
					printDebug("Entered Name");
				} else if (e.text.unicode == 8) { //Back Space
					input = input.substr(0, input.size()-1);
					inputText.setString(input);
                    updateCursor();
					updateScreen(window);
				} else {
					if(validateInput(e.text.unicode) && input.length() < maxChar) {
					char characterTyped = static_cast<char>(e.text.unicode);
                    input += characterTyped;
                    inputText.setString(input);
                    updateCursor();
					updateScreen(window);
					}	
				}

			} 
		}
	}
	return -1;
}

void InputScreen::initTextComponents() {
	sf::Vector2f location(WINDOW_WIDTH / 2.0f - inputBox.getSize().x / 2.0f,
        WINDOW_HEIGHT / 2.0f - inputBox.getSize().y / 2.0f - 5);
	inputText.setTextItems(*inputStr, location);
	queryText.setTextItems(queryMsg, sf::Vector2f(location.x,location.y-50), sf::Color::White,
		48);
	updateCursor();
}

void InputScreen::updateCursor() {
    sf::Vector2f coord = inputText.getPosition();
    coord.x += inputText.getGlobalBounds().width + 5;
    coord.y += 20;
    cursor.setPosition(coord);
}

bool InputScreen::validateInput(int ascii_id) {
    if (ascii_id >= 'A' && ascii_id <= 'Z') return true;
    if (ascii_id >= '0' && ascii_id <= '9') return true;
    return ascii_id >= 'a' && ascii_id <= 'z';
}

void InputScreen::initInputComponents() {
	inputBox.setSize(sf::Vector2f(WINDOW_WIDTH * 0.6f, 35.0f));
    inputBox.setOutlineThickness(-1);
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setFillColor(sf::Color::Black);

    inputBox.setPosition(WINDOW_WIDTH / 2.0f - inputBox.getSize().x / 2.0f,
        WINDOW_HEIGHT / 2.0f - inputBox.getSize().y / 2.0f);

    cursor.setSize(sf::Vector2f(2.0f, 27.0f));
    cursor.setOrigin(0, cursor.getSize().y / 2.0f);
    cursor.setFillColor(sf::Color::White);
}

void InputScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
   	window.draw(inputBox);
   	window.draw(cursor);
   	inputText.draw(window);
   	queryText.draw(window);
    window.display();
}