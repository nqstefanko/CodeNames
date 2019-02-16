#include "ConnectionScreen.hpp"

void ConnectionScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
    window.display();
}

ConnectionScreen::ConnectionScreen(bool & userType) {
	serverOrClient = &userType;
}

int ConnectionScreen::run(sf::RenderWindow & window) {
	while(window.isOpen()) {
		updateScreen(window);
		//updateCursor();
		sf::Event e;
		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) {
				printDebug("Closing Input String");
				window.close();
				return -1;
			} 
		}
	}
	return -1;
}