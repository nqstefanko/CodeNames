#include "ChoosingScreen.hpp"

ChoosingScreen::ChoosingScreen(bool & userType) {
	isServer = &userType;
}

int ChoosingScreen::run(sf::RenderWindow & window) {
	std::string input = "";
	while(window.isOpen()) {
		std::vector<Button> allButtons;
		Button client("Client", sf::Vector2f(window.getSize().x/3, window.getSize().y/3.5),
			sf::Vector2f(window.getSize().x/6, window.getSize().y/15), sf::Color::Blue,
			 window.getSize().y/15, 0);
		Button server("Server", sf::Vector2f(window.getSize().x/3, window.getSize().y/2),
			sf::Vector2f(window.getSize().x/6, window.getSize().y/15), sf::Color::Red,
			 window.getSize().y/15, 1);

		allButtons.push_back(client);
		allButtons.push_back(server);

		updateScreen(window, allButtons);
		allButtons[1].draw(window);
		sf::Event e;
		for(int i = 0; i < allButtons.size(); ++i) {
			if(allButtons[i].checkClick(window)) {
				printDebug("Clicked Button " + std::to_string(i));
				*isServer = i;
				if(*isServer) {
					printDebug("Clicked Server");
					return 2;
				} else {
					printDebug("Clicked Client");
					return 0;
				}
			}		
		}
		
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

void ChoosingScreen::updateScreen(sf::RenderWindow & window, std::vector<Button> & allButtons) {
	window.clear(sf::Color::Black);
	for(int i = 0; i < allButtons.size(); ++i) {
		allButtons[i].draw(window);
	}
    window.display();
}