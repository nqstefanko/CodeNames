#include "InputBox.hpp"

InputBox::InputBox(std::string & inputString, std::string queryMessage, int maxCharacter)
{
	inputStr = &inputString;
	queryMsg = queryMessage;
	maxChar = maxCharacter;
	initInputComponents();
	initTextComponents();
}

void InputBox::initInputComponents() {
	inputRect.setSize(sf::Vector2f(WINDOW_WIDTH * 0.6f, 35.0f));
    inputRect.setOutlineThickness(-1);
    inputRect.setOutlineColor(sf::Color::White);
    inputRect.setFillColor(sf::Color::Black);

    inputRect.setPosition(WINDOW_WIDTH / 12.5f - inputRect.getSize().x / 12.5f,
        WINDOW_HEIGHT / 3.2f - inputRect.getSize().y / 3.2f);

    cursor.setSize(sf::Vector2f(2.0f, 27.0f));
    cursor.setOrigin(0, cursor.getSize().y / 2.0f);
    cursor.setFillColor(sf::Color::White);
}

void InputBox::initTextComponents() {
	sf::Vector2f location(WINDOW_WIDTH / 12.0f - inputRect.getSize().x / 12.0f,
        WINDOW_HEIGHT / 3.2f - inputRect.getSize().y / 3.2f - 5);
	inputText.setTextItems(*inputStr, location);
	queryText.setTextItems(queryMsg, sf::Vector2f(location.x,location.y-50), sf::Color::White,
		48);
	updateCursor();
}

void InputBox::updateCursor() {
    sf::Vector2f coord = inputText.getPosition();
    coord.x += inputText.getGlobalBounds().width + 5;
    coord.y += 20;
    cursor.setPosition(coord);
}

bool InputBox::validateInput(int ascii_id) {
    if (ascii_id >= 'A' && ascii_id <= 'Z') return true;
    if (ascii_id >= '0' && ascii_id <= '9') return true;
    return (ascii_id >= 'a' && ascii_id <= 'z') || (ascii_id <= '.');
}


void InputBox::updateScreen(sf::RenderWindow & window) {
   	window.draw(inputRect);
   	window.draw(cursor);
   	inputText.draw(window);
   	queryText.draw(window);
}