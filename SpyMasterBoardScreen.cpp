#include "SpyMasterBoardScreen.hpp"

void canCloseItAll(sf::RenderWindow &app) {
	app.close();
	exit(0);
}

SpyMasterBoardScreen::SpyMasterBoardScreen(){}

std::vector<std::vector<int>> SpyMasterBoardScreen::makeTheBoard() {
	std::vector<int> allNumbers(25); // 25
	std::vector<std::vector<int>> toRet;
	std::iota (std::begin(allNumbers), std::end(allNumbers), 0);//Fill with 0-24 
	int count = 0;
	std::map<int, int> theTeamsMan;
	
	std::random_device device;
	std::default_random_engine engineOne{device()};
	std::default_random_engine engineTwo{device()};
	std::uniform_int_distribution<int> distributionOne{0, 1};

	while(count  < 17){
		std::uniform_int_distribution<int> distributionTwo{0, (int)(allNumbers.size()-1)};
		int rand = distributionTwo(engineTwo);

		//Take num 1-sizeOfArray, get num 1-25, and add to teams with 0 or 1
		theTeamsMan[allNumbers[rand]] = distributionOne(engineOne);
		allNumbers.erase (allNumbers.begin()+rand);
		++count;
	}

	std::uniform_int_distribution<int> distributionThree{0, (int)(allNumbers.size()-1)};
	int assassin = distributionThree(engineTwo);
	theTeamsMan[allNumbers[assassin]] = 2;
	allNumbers.erase (allNumbers.begin()+assassin);


	for(int i = 0; i < allNumbers.size();++i) {
		theTeamsMan[allNumbers[i]] = -1;
	}
	for(int i = 0; i < 5; ++i) {
		std::vector<int> temp;
		for(int j = 0; j < 5; ++j) {
			temp.push_back(theTeamsMan[(i*5)+j]);
		}
		toRet.push_back(temp);
	}
	return toRet;
}
void  SpyMasterBoardScreen::drawOnBoard(sf::RenderWindow &window) {

	Button QuitButton("Close", sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x/8, window.getSize().y/15),
			 sf::Color::Red, window.getSize().x/30,0);
	QuitButton.draw(window);
	int count = 0;
	std::vector<std::vector<int>> s = makeTheBoard();
	for(int i = 0; i < 5;++i) {
		for(int j = 0; j < 5;++j) {
			sf::Color todo=sf::Color::White;
			if(s[i][j] == 0) {
				todo = sf::Color::Red;
			} else if(s[i][j] == 1) {
				todo = sf::Color::Blue;
			} else if(s[i][j] == 2) {
				todo = sf::Color::Black;
			}
			sf::Vector2f tempButtonSize(window.getSize().x/8, window.getSize().y/10);
			sf::Vector2f tempButtonLoc(100+window.getSize().x/8+(j*50)+((window.getSize().x/8)*j),
                    50+window.getSize().y/10+(40*i)+((window.getSize().y/10)*i));

			Button tempBtn("",tempButtonLoc,tempButtonSize, todo,
				window.getSize().x/38,count);

			sf::Vector2f theShift(tempButtonLoc.x, 
				tempButtonLoc.y + 2*(window.getSize().y/100));
			std::cout << theShift.x << " " << theShift.y << std::endl;
			tempBtn.shiftTextInside(theShift, window);
			// temp.push_back(tempBtn);
			tempBtn.draw(window);
			count++;
		}
	}
}


int SpyMasterBoardScreen::Run(sf::RenderWindow &app) {
	sf::RenderWindow window(sf::VideoMode(1600, 900), "SpymasterBoard");

	//ButtonActions allBtnActions;
    //allBtnActions.update_keybind(0, &canCloseItAll);

	// std::vector<std::vector<int>> s = makeTheBoard();
	// for(int i = 0; i < 5; ++i) {
	// 	for(int j = 0; j < 5; ++j) {
	// 		std::cout << s[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	sf::Event event;
	bool running = true;
	window.clear(sf::Color::Black);
	// Button QuitButton("Close", sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x/8, window.getSize().y/15),
	// 	 sf::Color::Red, window.getSize().x/30,0);
	// QuitButton.draw(window);
	// int count = 0;

	// for(int i = 0; i < 5;++i) {
	// 	for(int j = 0; j < 5;++j) {
	// 		sf::Color todo=sf::Color::White;
	// 		if(s[i][j] == 0) {
	// 			todo = sf::Color::Red;
	// 		} else if(s[i][j] == 1) {
	// 			todo = sf::Color::Blue;
	// 		} else if(s[i][j] == 2) {
	// 			todo = sf::Color::Black;
	// 		}
	// 		sf::Vector2f tempButtonSize(window.getSize().x/8, window.getSize().y/10);
	// 		sf::Vector2f tempButtonLoc(100+window.getSize().x/8+(j*50)+((window.getSize().x/8)*j),
 //                    50+window.getSize().y/10+(40*i)+((app.getSize().y/10)*i));

	// 		Button tempBtn("",tempButtonLoc,tempButtonSize, todo,
	// 			window.getSize().x/38,count);

	// 		sf::Vector2f theShift(tempButtonLoc.x, 
	// 			tempButtonLoc.y + 2*(window.getSize().y/100));
	// 		std::cout << theShift.x << " " << theShift.y << std::endl;
	// 		tempBtn.shiftTextInside(theShift, window);
	// 		// temp.push_back(tempBtn);
	// 		tempBtn.draw(window);
	// 		count++;
	// 	}
	// }


    // run the program as long as the window is open

	while(running) {
		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) { //If Wind Closed
				std::cout << "Closing PlayBoard Screen" << std::endl;
				return -1;
			}

			
			window.display();
		}
	}
	return 0;
}




// 	sf::Event event;
// 	bool running = true;
// 	app.clear(sf::Color::Black);
// 	std::cout << "Running Opening Screen" << std::endl;

// 	Button QuitButton("Quit", sf::Vector2f(0, 0), sf::Vector2f(app.getSize().x/8, app.getSize().y/15),
// 		 sf::Color::Red, app.getSize().x/30,0);
// 	Text title("Codenames", sf::Vector2f(app.getSize().x/5, app.getSize().y/13), sf::Color::White,
// 	 app.getSize().x/10,"fonts/Xpressive Regular.ttf");
// 	Text menu("Menu", sf::Vector2f(app.getSize().x/2.5, app.getSize().y/4), sf::Color::Blue,
// 	 app.getSize().x/12,"fonts/Xpressive Regular.ttf");


// 	QuitButton.draw(app);
// 	LocalPlay.draw(app);
// 	MultiPlay.draw(app);
// 	title.draw(app);
// 	menu.draw(app);

// 	for(int i = 0; i < 5;++i) {
// 		std::vector<Button> temp;
// 		for(int j = 0; j < 5;++j) {
// 			sf::Vector2f tempButtonSize(app.getSize().x/8, app.getSize().y/10);
// 			sf::Vector2f tempButtonLoc(100+app.getSize().x/8+(j*50)+((app.getSize().x/8)*j),
//                     50+app.getSize().y/10+(40*i)+((app.getSize().y/10)*i));

// 			Button tempBtn(currentWords[count],tempButtonLoc,tempButtonSize, sf::Color::White,
// 				app.getSize().x/38,count);

// 			sf::Vector2f theShift(tempButtonLoc.x, 
// 				tempButtonLoc.y + 2*(app.getSize().y/100));
// 			std::cout << theShift.x << " " << theShift.y << std::endl;
// 			tempBtn.shiftTextInside(theShift, app);
// 			temp.push_back(tempBtn);
// 			tempBtn.draw(app);
// 			count++;
// 		}
// 	}


// 	while(running) {
// 		while(app.pollEvent(event)) {

// 			QuitButton.checkClick(app, allBtnActions);

// 			if(LocalPlay.checkClick(app, allBtnActions)) {
// 				return 1;
// 			}

// 			if(event.type == sf::Event::Closed) { //If Wind Closed
// 				std::cout << "Closing Opening Screen" << std::endl;
// 				return -1;
// 			}
			
// 			app.display();
// 		}
// 	}
// 	return 0;
// }