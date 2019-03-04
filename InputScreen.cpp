#include "InputScreen.hpp"

InputScreen::InputScreen(std::string & inputString, std::string & ip, 
	std::string queryMessage, int maxCharacter)
:inputItem(inputString,queryMessage,maxCharacter)
{
	ipAddress = &ip;
}


int InputScreen::run(sf::RenderWindow & window) {
	std::string input = "";
	while(window.isOpen()) {
		updateScreen(window);
		inputItem.updateCursor();
		sf::Event e;
		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) { //Dicon
				printDebug("Closing Input String");
				return DISCONNECT;
			} else if (e.type == sf::Event::TextEntered) {
				if(e.text.unicode == 10 || e.text.unicode == 13) {//Return 12
					printDebug("Entered " + input);
					*ipAddress = input;
					if(inputItem.queryMsg == "Enter IP Address Please") {
						printDebug(*ipAddress);
						return CONN_SCREEN;
					}

					inputItem.queryMsg = "Enter IP Address Please";
					inputItem.queryText.setString("Enter IP Address Please");
					*(inputItem.inputStr) = input;
					input = "";
					inputItem.inputText.setString("");
					return CHOOSE_SCREEN;

				} else if (e.text.unicode == 8) { //Back Space
					input = input.substr(0, input.size()-1);
					inputItem.inputText.setString(input);
                    inputItem.updateCursor();
					updateScreen(window);
				} else {
					if(inputItem.validateInput(e.text.unicode) && 
						(input.length() < inputItem.maxChar)) { //Text/Num
					char characterTyped = static_cast<char>(e.text.unicode);
                    input += characterTyped;
                    inputItem.inputText.setString(input);
                    inputItem.updateCursor();
					updateScreen(window);
					}	
				}

			} 
		}
	}
	return -1;
}

void InputScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
	inputItem.updateScreen(window);
    window.display();
}