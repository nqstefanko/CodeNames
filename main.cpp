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

	sf::RenderWindow App(sf::VideoMode(800, 450, 32), "SFML Window");
	App.setFramerateLimit(70);
	App.clear(sf::Color::Black);
	App.display(); //Clears Screen Initially Before Opening menu


	
	OpeningScreen menu;
	screenContainer.push_back(&menu);
	
	while (currentScreen >= 0)
	{
		currentScreen = screenContainer[currentScreen]->Run(App);

	}

	return EXIT_SUCCESS;
	
}