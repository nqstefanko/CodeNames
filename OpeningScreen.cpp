#include "OpeningScreen.hpp"

OpeningScreen::OpeningScreen(){}

void closeItAll(sf::RenderWindow &app) {
	app.close();
	exit(0);
}

void switchMeIp(sf::RenderWindow &app) {
	std::cout << "switching screens" << std::endl;
}

int OpeningScreen::Run(sf::RenderWindow &app) {

	ButtonActions allBtnActions;
    allBtnActions.update_keybind(0, &closeItAll);
    allBtnActions.update_keybind(1, &switchMeIp);


	sf::Event event;
	bool running = true;
	app.clear(sf::Color::Black);
	std::cout << "Running Opening Screen" << std::endl;

	Button QuitButton("Quit", sf::Vector2f(0, 0), sf::Vector2f(app.getSize().x/8, app.getSize().y/15),
		 sf::Color::Red, app.getSize().x/30,0);
	
	Button LocalPlay("Local", sf::Vector2f(app.getSize().x/2.5, app.getSize().y/2), 
		sf::Vector2f(app.getSize().x/6, app.getSize().y/10), sf::Color::Blue, app.getSize().x/18,1);

	Button MultiPlay("Multi", sf::Vector2f(app.getSize().x/2.5, app.getSize().y/2+app.getSize().y/10+50), 
		sf::Vector2f(app.getSize().x/6, app.getSize().y/10), sf::Color::Blue, app.getSize().x/18,0);

	Text title("Codenames", sf::Vector2f(app.getSize().x/5, app.getSize().y/13), sf::Color::White,
	 app.getSize().x/10,"fonts/Xpressive Regular.ttf");
	Text menu("Menu", sf::Vector2f(app.getSize().x/2.5, app.getSize().y/4), sf::Color::Blue,
	 app.getSize().x/12,"fonts/Xpressive Regular.ttf");


	QuitButton.draw(app);
	LocalPlay.draw(app);
	MultiPlay.draw(app);
	title.draw(app);
	menu.draw(app);


	while(running) {
		while(app.pollEvent(event)) {

			if(QuitButton.checkClick(app)) {
				allBtnActions.key_pressed(QuitButton.buttonId, app);//Do associated action with button
			}

			if(LocalPlay.checkClick(app)) {
				allBtnActions.key_pressed(LocalPlay.buttonId, app);//Do associated action with button
				return 1;
				break;
			}

			if(event.type == sf::Event::Closed) { //If Wind Closed
				std::cout << "Closing Opening Screen" << std::endl;
				return -1;
			}
			
			app.display();
		}
	}
	return 0;
}

OpeningScreen::~OpeningScreen(){}