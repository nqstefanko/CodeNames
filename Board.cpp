#include "Board.hpp"

Board::Board(){}

std::vector<std::vector<int>> generate5x5Board(
	std::map<int, std::vector<int>> &teamBreakdown) {
	std::vector<int> allNumbers(25); // 25
	std::vector<int> spiesAndAssassin(25); // 25
	std::vector<std::vector<int>> toRet;

	std::iota (std::begin(allNumbers), std::end(allNumbers), 0);//Fill with 0-24 
	int count = 0;

	std::random_device device;//Spawn random device
	std::default_random_engine engineOne{device()};
	std::map<int, int> theTeamsMan;

	while(count  < 12){
		std::uniform_int_distribution<int> distributionTwo{0, (int)(allNumbers.size()-1)};
		int rand = distributionTwo(engineOne);
		int temp = (count>=9) ? 1 : 0;
		theTeamsMan[allNumbers[rand]] = (count>=9) ? 1 : 0;
		teamBreakdown[temp].push_back(allNumbers[rand]);
		allNumbers.erase (allNumbers.begin()+rand);
		++count;
	}

	for(int i = 0; i < allNumbers.size();++i) {
		theTeamsMan[allNumbers[i]] = -1;//Make neutral
		teamBreakdown[-1].push_back(allNumbers[i]);
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

	// int assassinToNeutral = teamBreakdown[1][0];
	// int assassinToGreen = teamBreakdown[1][1];
	// int assassinToAssassin = teamBreakdown[1][2];
	// int greenToAssassin = teamBreakdown[0][0];
	// int neurtalToAssassin = teamBreakdown[-1][0];

std::vector<std::vector<int>> generateOpposingBoard(
	std::map<int, std::vector<int>> &teamBreakdown) {

	std::map<int, std::vector<int>> newTeamBreakdown;
	std::vector<int> newVec(teamBreakdown[0].begin(),
	  teamBreakdown[0].begin()+3);
	newTeamBreakdown[0] = newVec;//Shared Green Cards 3
	newTeamBreakdown[1].push_back(teamBreakdown[1][0]);//AssassinToAssassin
	newTeamBreakdown[0].push_back(teamBreakdown[1][1]);//AssassinToGren
	newTeamBreakdown[-1].push_back(teamBreakdown[1][2]);//AssassinToNeurta;
	newTeamBreakdown[1].push_back(teamBreakdown[0][3]);//GreeenToAssassin
	newTeamBreakdown[1].push_back(teamBreakdown[-1][0]);//neurtalToAssassin
	for (int i = 4; i < teamBreakdown[0].size();i++) {
		newTeamBreakdown[-1].push_back(teamBreakdown[0][i]);
	}



	std::vector<int> allNumbers(25); // 25
	std::vector<int> toConvert(25); // 25
	std::vector<std::vector<int>> toRet;

	std::iota (std::begin(allNumbers), std::end(allNumbers), 0);//Fill with 0-24 
	for(int i = -1; i < 2; i++) {
		for (auto num: newTeamBreakdown[i]) {
			allNumbers.erase(std::remove(std::begin(allNumbers), std::end(allNumbers), num),
          		std::end(allNumbers));
		}
	}


	int count = 0;

	std::random_device device;//Spawn random device
	std::default_random_engine engineOne{device()};
	std::map<int, int> theTeamsMan;

	while(count  < 5){
		std::uniform_int_distribution<int> distributionTwo{0, (int)(allNumbers.size()-1)};
		int rand = distributionTwo(engineOne);

		newTeamBreakdown[0].push_back(allNumbers[rand]);
		allNumbers.erase (allNumbers.begin()+rand);
		++count;
	}

	for(int i = 0; i < allNumbers.size();++i) {
		newTeamBreakdown[-1].push_back(allNumbers[i]);
	}


	std::iota (std::begin(allNumbers), std::end(allNumbers), 0);//Fill with 0-24 
	for(int i = -1; i < 2; i++) {
		for (auto num: newTeamBreakdown[i]) {
			toConvert[num] = i;
		}
	}
	// for (auto e: toConvert) {
	// 	std::cout << e << " ";
	// }
	std::cout << std::endl;

	for(int i = 0; i < 5; ++i) {
		std::vector<int> temp;
		for(int j = 0; j < 5; ++j) {
			temp.push_back(toConvert[(i*5)+j]);
		}
		toRet.push_back(temp);
	}
	return toRet;
}

void printBoard(std::vector<std::vector<int>> board) {
	for(int i = 0; i < 5; ++i) {
		std::cout << "[";
		for(int j = 0; j < 5; ++j) {
			std::cout << board[i][j] << ", ";
		}
		std::cout << "]"<<std::endl;
	}
}

//3 and 1 greens, 2 assassins, and one neutral 
void Board::generateBoards() {
	std::map<int, std::vector<int>> teamBreakdown;
	std::vector<std::vector<int>> boardOneStructure = generate5x5Board(teamBreakdown);
	std::vector<std::vector<int>> boardOneStructure = generateOpposingBoard(teamBreakdown);
}

// #include "SpyMasterBoardScreen.hpp"

// void canCloseItAll(sf::RenderWindow &app) {
// 	app.close();
// 	exit(0);
// }

// SpyMasterBoardScreen::SpyMasterBoardScreen(){}

// std::vector<std::vector<int>> SpyMasterBoardScreen::makeTheBoard() {
// 	std::vector<int> allNumbers(25); // 25
// 	std::vector<std::vector<int>> toRet;
// 	std::iota (std::begin(allNumbers), std::end(allNumbers), 0);//Fill with 0-24 
// 	int count = 0;
// 	std::map<int, int> theTeamsMan;
	
// 	std::random_device device;
// 	std::default_random_engine engineOne{device()};
// 	std::default_random_engine engineTwo{device()};
// 	std::uniform_int_distribution<int> distributionOne{0, 1};

// 	while(count  < 17){
// 		std::uniform_int_distribution<int> distributionTwo{0, (int)(allNumbers.size()-1)};
// 		int rand = distributionTwo(engineTwo);

// 		//Take num 1-sizeOfArray, get num 1-25, and add to teams with 0 or 1
// 		theTeamsMan[allNumbers[rand]] = distributionOne(engineOne);
// 		allNumbers.erase (allNumbers.begin()+rand);
// 		++count;
// 	}

// 	std::uniform_int_distribution<int> distributionThree{0, (int)(allNumbers.size()-1)};
// 	int assassin = distributionThree(engineTwo);
// 	theTeamsMan[allNumbers[assassin]] = 2;
// 	allNumbers.erase (allNumbers.begin()+assassin);


// 	for(int i = 0; i < allNumbers.size();++i) {
// 		theTeamsMan[allNumbers[i]] = -1;
// 	}
// 	for(int i = 0; i < 5; ++i) {
// 		std::vector<int> temp;
// 		for(int j = 0; j < 5; ++j) {
// 			temp.push_back(theTeamsMan[(i*5)+j]);
// 		}
// 		toRet.push_back(temp);
// 	}
// 	return toRet;
// }
// void  SpyMasterBoardScreen::drawOnBoard(sf::RenderWindow &window) {

// 	Button QuitButton("Close", sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x/8, window.getSize().y/15),
// 			 sf::Color::Red, window.getSize().x/30,0);
// 	QuitButton.draw(window);
// 	int count = 0;
// 	std::vector<std::vector<int>> s = makeTheBoard();
// 	for(int i = 0; i < 5;++i) {
// 		for(int j = 0; j < 5;++j) {
// 			sf::Color todo=sf::Color::White;
// 			if(s[i][j] == 0) {
// 				todo = sf::Color::Red;
// 			} else if(s[i][j] == 1) {
// 				todo = sf::Color::Blue;
// 			} else if(s[i][j] == 2) {
// 				todo = sf::Color::Black;
// 			}
// 			sf::Vector2f tempButtonSize(window.getSize().x/8, window.getSize().y/10);
// 			sf::Vector2f tempButtonLoc(100+window.getSize().x/8+(j*50)+((window.getSize().x/8)*j),
//                     50+window.getSize().y/10+(40*i)+((window.getSize().y/10)*i));

// 			Button tempBtn("",tempButtonLoc,tempButtonSize, todo,
// 				window.getSize().x/38,count);

// 			sf::Vector2f theShift(tempButtonLoc.x, 
// 				tempButtonLoc.y + 2*(window.getSize().y/100));
// 			std::cout << theShift.x << " " << theShift.y << std::endl;
// 			tempBtn.shiftTextInside(theShift, window);
// 			// temp.push_back(tempBtn);
// 			tempBtn.draw(window);
// 			count++;
// 		}
// 	}
// }


// int SpyMasterBoardScreen::Run(sf::RenderWindow & app) {

// 	ButtonActions allBtnActions;
//     allBtnActions.update_keybind(0, &canCloseItAll);

// 	std::vector<std::vector<int>> s = makeTheBoard();
// 	for(int i = 0; i < 5; ++i) {
// 		for(int j = 0; j < 5; ++j) {
// 			std::cout << s[i][j] << " ";
// 		}
// 		std::cout << std::endl;
// 	}
// 	sf::Event event;
// 	bool running = true;
// 	app.clear(sf::Color::Black);
// 	Button QuitButton("Close", sf::Vector2f(0, 0), sf::Vector2f(app.getSize().x/8, app.getSize().y/15),
// 		 sf::Color::Red, app.getSize().x/30,0);
// 	QuitButton.draw(app);
// 	int count = 0;

// 	for(int i = 0; i < 5;++i) {
// 		for(int j = 0; j < 5;++j) {
// 			sf::Color todo=sf::Color::White;
// 			if(s[i][j] == 0) {
// 				todo = sf::Color::Red;
// 			} else if(s[i][j] == 1) {
// 				todo = sf::Color::Blue;
// 			} else if(s[i][j] == 2) {
// 				todo = sf::Color::Black;
// 			}
// 			sf::Vector2f tempButtonSize(app.getSize().x/8, app.getSize().y/10);
// 			sf::Vector2f tempButtonLoc(100+app.getSize().x/8+(j*50)+((app.getSize().x/8)*j),
//                     50+app.getSize().y/10+(40*i)+((app.getSize().y/10)*i));

// 			Button tempBtn("",tempButtonLoc,tempButtonSize, todo,
// 				app.getSize().x/38,count);

// 			sf::Vector2f theShift(tempButtonLoc.x, 
// 				tempButtonLoc.y + 2*(app.getSize().y/100));
// 			std::cout << theShift.x << " " << theShift.y << std::endl;
// 			tempBtn.shiftTextInside(theShift, app);
// 			// temp.push_back(tempBtn);
// 			tempBtn.draw(app);
// 			count++;
// 		}
// 	}


//     // run the program as long as the window is open

// 	while(running) {
// 		while(app.pollEvent(event)) {
// 			if(QuitButton.checkClick(app)) {
// 				return 1;
// 				break;

// 			}
// 			if(event.type == sf::Event::Closed) { //If Wind Closed
// 				std::cout << "Closing PlayBoard Screen" << std::endl;
// 				return 1;
// 				break;
// 			}
			
// 			app.display();
// 		}
// 	}
// 	return 0;
// }




// // 	sf::Event event;
// // 	bool running = true;
// // 	app.clear(sf::Color::Black);
// // 	std::cout << "Running Opening Screen" << std::endl;

// // 	Button QuitButton("Quit", sf::Vector2f(0, 0), sf::Vector2f(app.getSize().x/8, app.getSize().y/15),
// // 		 sf::Color::Red, app.getSize().x/30,0);
// // 	Text title("Codenames", sf::Vector2f(app.getSize().x/5, app.getSize().y/13), sf::Color::White,
// // 	 app.getSize().x/10,"fonts/Xpressive Regular.ttf");
// // 	Text menu("Menu", sf::Vector2f(app.getSize().x/2.5, app.getSize().y/4), sf::Color::Blue,
// // 	 app.getSize().x/12,"fonts/Xpressive Regular.ttf");


// // 	QuitButton.draw(app);
// // 	LocalPlay.draw(app);
// // 	MultiPlay.draw(app);
// // 	title.draw(app);
// // 	menu.draw(app);

// // 	for(int i = 0; i < 5;++i) {
// // 		std::vector<Button> temp;
// // 		for(int j = 0; j < 5;++j) {
// // 			sf::Vector2f tempButtonSize(app.getSize().x/8, app.getSize().y/10);
// // 			sf::Vector2f tempButtonLoc(100+app.getSize().x/8+(j*50)+((app.getSize().x/8)*j),
// //                     50+app.getSize().y/10+(40*i)+((app.getSize().y/10)*i));

// // 			Button tempBtn(currentWords[count],tempButtonLoc,tempButtonSize, sf::Color::White,
// // 				app.getSize().x/38,count);

// // 			sf::Vector2f theShift(tempButtonLoc.x, 
// // 				tempButtonLoc.y + 2*(app.getSize().y/100));
// // 			std::cout << theShift.x << " " << theShift.y << std::endl;
// // 			tempBtn.shiftTextInside(theShift, app);
// // 			temp.push_back(tempBtn);
// // 			tempBtn.draw(app);
// // 			count++;
// // 		}
// // 	}


// // 	while(running) {
// // 		while(app.pollEvent(event)) {

// // 			QuitButton.checkClick(app, allBtnActions);

// // 			if(LocalPlay.checkClick(app, allBtnActions)) {
// // 				return 1;
// // 			}

// // 			if(event.type == sf::Event::Closed) { //If Wind Closed
// // 				std::cout << "Closing Opening Screen" << std::endl;
// // 				return -1;
// // 			}
			
// // 			app.display();
// // 		}
// // 	}
// // 	return 0;
// // }