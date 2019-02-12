#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>    

#include "Util.hpp"
#include "InputScreen.hpp"

int main(int argc, char ** argv) {
	std::vector<CScreen*> screenContainer;
	int currentScreen = 0;


	sf::TcpSocket socket;
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "SFML Window");
	window.setFramerateLimit(FPS);
	window.clear(sf::Color::Black);
	window.display(); //Clears Screen Initially Before Opening menu
	
	std::string username = "";


	InputScreen startScreen(username, std::string("Enter your name (Max 15 Characters)"), 15);
	screenContainer.push_back(&startScreen);
	
	while (currentScreen >= 0)
	{
		currentScreen = screenContainer[currentScreen]->run(window);
	}

	printDebug("Closing Program");

	return 0;
	
}