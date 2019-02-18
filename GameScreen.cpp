#include "GameScreen.hpp"

GameScreen::GameScreen(){}

void GameScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::White);
    window.display();
}


int GameScreen::run(sf::RenderWindow & window) {
	while(window.isOpen()) {
		updateScreen(window);

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