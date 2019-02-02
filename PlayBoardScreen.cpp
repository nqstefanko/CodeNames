#include "PlayBoardScreen.hpp"
PlayBoardScreen::PlayBoardScreen(){}

void closeItAllNow(sf::RenderWindow &app) {
	app.close();
	exit(0);
}

int PlayBoardScreen::Run(sf::RenderWindow &app) {
	std::vector<std::vector<Button>> allCodeNames;
	WordGenerator codeDict("allCodenameWords.txt");
	int count = 0;
	sf::Event event;
	bool running = true;
	app.clear(sf::Color::Black);
	std::vector<std::string> currentWords = codeDict.generateWords(25);
	for(int i =0;i< 25;i++) {
		std::cout << currentWords[i] << std::endl;
	}
	for(int i = 0; i < 5;++i) {
		std::vector<Button> temp;
		for(int j = 0; j < 5;++j) {
			sf::Vector2f tempButtonSize(app.getSize().x/8, app.getSize().y/10);
			sf::Vector2f tempButtonLoc(100+app.getSize().x/8+(j*50)+((app.getSize().x/8)*j),
                    50+app.getSize().y/10+(40*i)+((app.getSize().y/10)*i));

			Button tempBtn(currentWords[count],tempButtonLoc,tempButtonSize, sf::Color::White,
				app.getSize().x/38,count);

			sf::Vector2f theShift(tempButtonLoc.x, 
				tempButtonLoc.y + 2*(app.getSize().y/100));
			std::cout << theShift.x << " " << theShift.y << std::endl;
			tempBtn.shiftTextInside(theShift, app);
			temp.push_back(tempBtn);
			tempBtn.draw(app);
			count++;
		}
	}

	Button QuitButton("Quit", sf::Vector2f(0, 0), sf::Vector2f(app.getSize().x/12, app.getSize().y/16),
	 sf::Color::Red, app.getSize().x/30,0);

	QuitButton.draw(app);

	ButtonActions allBtnActions;
    allBtnActions.update_keybind(0, &closeItAllNow);


	while(running) {
		while(app.pollEvent(event)) {

			QuitButton.checkClick(app, allBtnActions);
			if(event.type == sf::Event::Closed) { //If Wind Closed
				std::cout << "Closing Opening Screen" << std::endl;
				return -1;
			}
			
			app.display();
		}
	}
	return 0;
}
