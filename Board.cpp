#include "Board.hpp"

Board::Board()
{
	words = generator.generateWords();
	std::random_shuffle ( words.begin(), words.end() );

}

std::vector<std::vector<int>> Board::generate5x5Board() {

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
		theTeamsMan[allNumbers[i]] = 2;//Make neutral
		teamBreakdown[2].push_back(allNumbers[i]);
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



std::vector<std::vector<int>> Board::generateOpposingBoard() {

	std::map<int, std::vector<int>> newTeamBreakdown;
	std::vector<int> newVec(teamBreakdown[0].begin(),
	  teamBreakdown[0].begin()+3);
	newTeamBreakdown[0] = newVec;//Shared Green Cards 3
	newTeamBreakdown[1].push_back(teamBreakdown[1][0]);//AssassinToAssassin
	newTeamBreakdown[0].push_back(teamBreakdown[1][1]);//AssassinToGren
	newTeamBreakdown[2].push_back(teamBreakdown[1][2]);//AssassinToNeurta;
	newTeamBreakdown[1].push_back(teamBreakdown[0][3]);//GreeenToAssassin
	newTeamBreakdown[1].push_back(teamBreakdown[2][0]);//neurtalToAssassin
	for (int i = 4; i < teamBreakdown[0].size();i++) {
		newTeamBreakdown[2].push_back(teamBreakdown[0][i]);
	}

	std::vector<int> allNumbers(25); // 25
	std::vector<int> toConvert(25); // 25
	std::vector<std::vector<int>> toRet;

	std::iota (std::begin(allNumbers), std::end(allNumbers), 0);//Fill with 0-24 
	for(int i = 0; i < 3; i++) {
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
		newTeamBreakdown[2].push_back(allNumbers[i]);
	}


	std::iota (std::begin(allNumbers), std::end(allNumbers), 0);//Fill with 0-24 
	for(int i = 0; i < 3; i++) {
		for (auto num: newTeamBreakdown[i]) {
			toConvert[num] = i;
		}
	}

	std::cout << std::endl;

	for(int i = 0; i < 5; ++i) {
		std::vector<int> temp;
		for(int j = 0; j < 5; ++j) {
			temp.push_back(toConvert[(i*5)+j]);
		}
		toRet.push_back(temp);
	}
	opponentBreakdown = newTeamBreakdown;
	return toRet;
}

//3 and 1 greens, 2 assassins, and one neutral 
void Board::generateBoards() {
	
	boardOneStructure = generate5x5Board();
	boardTwoStructure = generateOpposingBoard();
	makeBoardUI();
	// printBoard(boardOneStructure);
	// printBoard(boardTwoStructure);
}

void Board::makeBoardUI() {
	int count = 0;
	for(int i = 0; i < 5; ++i) {
		std::vector<Button> temp;
		for(int j = 0; j < 5; ++j) {
			sf::Vector2f tempButtonSize(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 12);
			sf::Vector2f tempButtonLoc(WINDOW_WIDTH / 32 + (j * 30) + 
				((WINDOW_WIDTH / 8) * j), WINDOW_HEIGHT / 30 + WINDOW_HEIGHT / 3
				 + (20 * i) + ((WINDOW_HEIGHT / 10) * i));
			//std::cout << words[count] << " " << i << " " <<  j << std::endl;
			printDebug(words[count]);
			std::string s = words[count];
			Button tempBtn(s, tempButtonLoc, tempButtonSize,
			sf::Color::Black, WINDOW_WIDTH / 38, count);

			sf::Vector2f theShift(tempButtonLoc.x, 
				tempButtonLoc.y + 2 * (WINDOW_HEIGHT / 100));

			tempBtn.shiftTextInside(theShift);
			temp.push_back(tempBtn);
			count++;
		}
		boardOneColorsUI.push_back(temp);
	}
}

void Board::drawBoard(sf::RenderWindow & window) {
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 5; ++j) {		
			boardOneColorsUI[i][j].draw(window);
		}
	}
}

void Board::drawMiniColorBoard(sf::RenderWindow & window, int boardNumber) {
	int count = 0;
	for(int i = 0; i < 5; ++i) {
		std::vector<Button> temp;
		for(int j = 0; j < 5; ++j) {
			sf::Vector2f tempButtonSize(window.getSize().x / 32, window.getSize().y/36);
			sf::Vector2f tempButtonLoc(window.getSize().x/1.5 + (j * 15) + 
				((window.getSize().x / 32) * j), window.getSize().y / 30 + 
				window.getSize().y / 30 + (10 * i) + ((window.getSize().y/30) * i));
			std::vector<std::vector<int>> * boardPtr;
			Button tempBtn("", tempButtonLoc, tempButtonSize,
				sf::Color::Black, window.getSize().x/38, count);

			if(boardNumber == 1) {
				boardPtr = &boardOneStructure;
			} else {
				boardPtr = &boardTwoStructure;
			}

			switch((*boardPtr)[i][j]) {
				case 0: //Green
					tempBtn.setColor(sf::Color::Green);
					break;
				case 1: //Assassin
					tempBtn.setColor(sf::Color::Black);
					break;
				default: //Bystander
					tempBtn.setColor(sf::Color::White);
					break;
			}

			sf::Vector2f theShift(tempButtonLoc.x, 
				tempButtonLoc.y + 2 * (window.getSize().y/100));

			temp.push_back(tempBtn);
			tempBtn.draw(window);
			count++;
		}
	}
}


void Board::setBoard(std::string allBoardValues, int boardNumber) {
	teamBreakdown.clear();
	for(int count = 0; count < allBoardValues.length();++count) {
		int i = count/5;
		int j = count%5;
		int num = allBoardValues[count] -'0';//get at index and set that 0,1,2
		teamBreakdown[allBoardValues[count]].push_back(count);
		if(boardNumber == 1) {
			boardOneColorsUI[i][j].setText(words[count]);
			boardOneStructure[i][j] = num; //player/client
		} else {
			boardTwoStructure[i][j] = num; //opponent/server
		}
	}
}

std::string Board::getBoardValues(int num) {
	std::string toRet;
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 5; ++j) {
			if(num == 1) {
				toRet+=std::to_string(boardOneStructure[i][j]);
			} else {
				toRet+=std::to_string(boardTwoStructure[i][j]);
			}
		}
	}
	return toRet;
}

void Board::setWords(std::string newWord, int num) {
	words[num] = newWord;
}



	// for(int i = 0; i < 3; i++) {
	// 	std::cout << i << ": ";
	// 	for (auto num: teamBreakdown[i]) {
	// 		std::cout << num << " ";
	// 	}
	// 	std::cout << std::endl;
	// }

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
// // 	 app.getSize().x/10,FONTF);
// // 	Text menu("Menu", sf::Vector2f(app.getSize().x/2.5, app.getSize().y/4), sf::Color::Blue,
// // 	 app.getSize().x/12,FONTF);


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