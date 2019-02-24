#include "GameScreen.hpp"

GameScreen::GameScreen(Board & newBoard,std::string & inputString, bool & userType):
	inputItem(inputString), 
	turnsLeft("Turns:9", sf::Vector2f(WINDOW_WIDTH/1.25, WINDOW_HEIGHT/1.5), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" ),
	agentsLeft("Agents:15", sf::Vector2f(WINDOW_WIDTH/1.25, WINDOW_HEIGHT/1.75), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" )
{
	isServer = &userType;
	boardPtr = &newBoard;
}

void GameScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
	boardPtr->drawBoard(window);
	if(*isServer){
		boardPtr->drawMiniColorBoard(window, 1);
	} else {
		boardPtr->drawMiniColorBoard(window, 2);
	}
	turnsLeft.draw(window);
	agentsLeft.draw(window);
	inputItem.updateScreen(window);
    window.display();
}


int GameScreen::run(sf::RenderWindow & window) {
	while(window.isOpen()) {
		updateScreen(window);
		inputItem.updateCursor();
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