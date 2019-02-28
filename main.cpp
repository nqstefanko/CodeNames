#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>    

#include "InputBox.hpp"
#include "Util.hpp"
#include "InputScreen.hpp"
#include "ChoosingScreen.hpp"
#include "ConnectionScreen.hpp"
#include "GameScreen.hpp"
#include "Board.hpp"

int main(int argc, char ** argv) {
	std::vector<CScreen*> screenContainer;
	int currentScreen = 0;
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "SFML Window");
	window.setFramerateLimit(FPS);
	window.clear(sf::Color::Black);
	window.display(); //Clears Screen Initially Before Opening menu
		
	sf::TcpSocket socket;
	std::string username = "";
	std::string codeword = "";
	std::string ip = "";
	bool serverUser = false;

	Board gameboard;
	gameboard.generateBoards();

	InputScreen startScreen(username,ip, std::string("Enter your name (Max 20 Characters)"), 20);
	screenContainer.push_back(&startScreen);

	ChoosingScreen chooseScreen(serverUser);
	screenContainer.push_back(&chooseScreen);

	ConnectionScreen connScreen(serverUser, socket, username,ip);
	screenContainer.push_back(&connScreen);

	GameScreen game(gameboard, codeword, serverUser, username, socket);
	screenContainer.push_back(&game);
	
	while (currentScreen >= 0)
	{
		currentScreen = screenContainer[currentScreen]->run(window);
	}

	printDebug("Closing Program");

	return 0;
	
}