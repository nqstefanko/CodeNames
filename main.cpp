#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "AllScreens.hpp"
#include "Button.hpp"
#include "ButtonActions.hpp"
#include "Text.hpp"

int main(int argc, char ** argv) {
	std::vector<CScreen*> screenContainer;
	int currentScreen = 0;

	sf::RenderWindow App(sf::VideoMode(1600, 900, 32), "SFML Window");
	App.setFramerateLimit(70);
	App.clear(sf::Color::Black);
	App.display(); //Clears Screen Initially Before Opening menu


	
	OpeningScreen menu;
	screenContainer.push_back(&menu);
	
	PlayBoardScreen gameboard;
	screenContainer.push_back(&gameboard);
	
	while (currentScreen >= 0)
	{
		currentScreen = screenContainer[currentScreen]->Run(App);
	}

	return EXIT_SUCCESS;
	
}