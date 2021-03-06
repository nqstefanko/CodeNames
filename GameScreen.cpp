#include "GameScreen.hpp"

GameScreen::GameScreen(Board & newBoard,std::string & inputString, bool & userType,
	std::string &user, sf::TcpSocket & sock):
	inputItem(inputString), 
	turnsLeft("Turns:9", getV2f(1.25, 1.5, true), sf::Color::White, 48, FONTF),
	agentsLeft("Agents:0", getV2f(1.25, 1.75, true), sf::Color::White, 48, FONTF),
	agentTurn("Agent: " + user + "'s Turn" , getV2f(40, 10, true),
		sf::Color::Blue, 48, FONTF),
	currentClue("Current Clue: Waiting on Sender!", getV2f(40, 30, true),
		sf::Color::Green, 48, FONTF ),
	guessText("Guesses:", getV2f(1.25, 1.25, true), sf::Color::White, 36, FONTF),
	endTurnButton("End\nTurn",getV2f(1.5, 3.5, true),getV2f(14, 15, true), 
		sf::Color::Red, 32, 50)
	
{
	std::cout << userType << user << std::endl;
	isServer = &userType;
	boardPtr = &newBoard;
	username = &user;
	socket = &sock;
	setUpDone = false;
	hintNum = 1;
	win = false;
	turns = 9;
	agentOnBoardLeft = 9;
	opponentsAgentsLeft = 9;
	agents = 0;
	finalTurn = false;
	disconnect = false;
	for(int i = 0; i < 10; ++i) { //Draw 1-9 Buttons
		sf::Vector2f tempButtonSize(WINDOW_WIDTH / 40, WINDOW_HEIGHT / 20);
		sf::Vector2f tempButtonLoc(WINDOW_WIDTH / 1.35, 
			WINDOW_HEIGHT / 3.35 +((WINDOW_HEIGHT / 16) + 3) * i );
		Button tempBtn(std::to_string(i), tempButtonLoc, tempButtonSize,
			sf::Color(16, 117, 24, 255), WINDOW_WIDTH / 38, i + 1100);
		allHintNumbers.push_back(tempBtn);
	}
}

//204, 232, 255


void GameScreen::restartTheGame() {
	setUpDone = false;
	hintNum = 1;
	win = false;
	turns = 2;
	agentOnBoardLeft = 9;
	opponentsAgentsLeft = 9;
	agents = 0;
	finalTurn = false;
	disconnect = false;
}


void GameScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
	boardPtr->drawBoard(window);
	makeActionText();
	boardPtr->drawMiniColorBoard(window, 1);

	allHintNumbers[hintNum].setColor(sf::Color::Magenta);

	Text codenamesLogo("Codenames Duet", sf::Vector2f(WINDOW_WIDTH / 3, 0), 
		sf::Color::Green, 42, FONTF );
	if(suddenDeath) {
		turnsLeft.setString("SUDDEN DEATH");
		agentTurn.setString("YOUR TURN!");
	} else {
		turnsLeft.setString("Turns:" + std::to_string(turns));
	}
	turnsLeft.draw(window);
	agentsLeft.setString("Agents:" + std::to_string(agents));
	agentsLeft.draw(window);
	setProperTurnColor();
	agentTurn.draw(window);
	if(state == GAMEOVER) {
		std::string gameOverText = "";
		sf::Color t = sf::Color::Red;
		if(!win) {
			gameOverText = "LOSER!";
		} else {
			gameOverText = "WINNER!";
			t = sf::Color::Green;
		}
		Text gameOverBigBoi(gameOverText, getV2f(3, 22, true), t, 128, FONTF);
		gameOverBigBoi.draw(window);
	}
	if(state == WAITING_FOR_CLICK) {
		endTurnButton.draw(window);
	}

	if(state == SUDDEN_DEATH) {
		if(opponentsAgentsLeft == 0) {
			guessText.setString("No more Agents\n Wait on: " + opponentName);
			guessText.draw(window);
		}
	}

	for(int i = 0; i < 10; ++i) {
		allHintNumbers[i].draw(window); //Draw 1-9 Buttons
	}
	
	currentClue.draw(window);
	codenamesLogo.draw(window);
	inputItem.updateScreen(window);
    
    window.display();
}

void GameScreen::makeActionText() {
	switch(state) {
		case WAITING_FOR_INPUT: { //Oringally Client
			agentTurn.setString("Your Turn: Type a Hint!");
			break;
		} 
		case WAITING_FOR_HINT: { //Originally Server!
			agentTurn.setString(opponentName + "'s' Turn: Waiting on Hint!");
			break;
		}
		case WAITING_FOR_CLICK: { //Waiting for user to click codewords
			agentTurn.setString("Your Turn: Click Codewords!");
			break; 
		}
		case WAITING_FOR_GUESS: { //Waiting to user to SEND codeword clicks
			agentTurn.setString(opponentName + "'s' Turn: Waiting on Guesses!");
			break; 
		}
	}
}


void GameScreen::setUpBoardsMyBoi() {
	sf::Packet packetWord;
	sf::Packet packetBoard;
	sf::Packet sendName;

	std::set<std::string> newWords;
	std::string boardStr;
	std::string currentWord;
	std::string s;

	if(*isServer) {//SERVER SIDE!!
		allHintNumbers[hintNum].setColor(sf::Color::Magenta);
		std::string b1;
		std::string b2;
		std::string oppName;
		state = WAITING_FOR_HINT;
		printDebug("SERVER: STATE IS WAINTING FOR HINT!!");

		int i;
		int count = 0;
		sf::Packet packetWordRecieve;

		while(newWords.size() != 25) {
			sf::Packet packetBoardRecieve;
			socket->receive(packetWordRecieve);
			if (packetWordRecieve >> s >> i) //Getting all words and indexes
			{
				std::cout << "Recieved: " << s << " " << i << std::endl;
			    if(newWords.find(s) == newWords.end()) { //if not in bro
				    newWords.insert(s);
				    allWords.push_back(s);
				    boardPtr->words[i] = s;
			    }
			    packetWordRecieve.clear();
			}			
		}
		socket->receive(packetWordRecieve);
		if (packetWordRecieve >> b1 >> b2 >> oppName) //Getting boards and opponent name!
		{
			boardPtr->setBoard(b1, 2);
			boardPtr->setBoard(b2, 1);
			opponentName = oppName;
			std::cout << "Printing Boards Server!" << std::endl;
			// printBoard(boardPtr->boardOneStructure);//should be mine
			// std::cout << std::endl;
			// printBoard(boardPtr->boardTwoStructure);//should be oppo
			boardPtr->makeBoardUI();
			sendName << *username;
			socket->send(sendName);
			return;
		}



	} else {//CLIENT SIDE
		state = WAITING_FOR_INPUT;
		printDebug("CLIENT: STATE IS WAINTING FOR INPUT!!");
		allHintNumbers[hintNum].setColor(sf::Color::Magenta);

		packetBoard << boardPtr->getBoardValues(1);
		packetBoard << boardPtr->getBoardValues(2);
		packetBoard << *username;

		for(int i = 0; i < 25; i++) {
			//printDebug("Sending on ClientSide " + boardPtr->words[i] + " " + std::to_string(i));
			allWords.push_back(boardPtr->words[i]);
			packetWord << boardPtr->words[i] << i;
			if (socket->send(packetWord) != sf::Socket::Done)
			{
			    printDebug("Fuck error");
			}
			packetWord.clear();
		}
		//printDebug("Sending PB: " + boardPtr->getBoardValues(2));
		socket->send(packetBoard);
		socket->receive(sendName);
		if (sendName >> s)
		{
			opponentName = s;
		}

		std::cout << "Printing Boards Client!" << std::endl;
		// printBoard(boardPtr->boardOneStructure);//should be mine
		// std::cout << std::endl;
		// printBoard(boardPtr->boardTwoStructure);//should be oppo
		return;
	}

}

void GameScreen::setProperTurnColor() {
	//std::cout << "HERE: "<< *isServer << " " << state << " " << std::endl;
	if(*isServer) {
		if(state == WAITING_FOR_CLICK || state == WAITING_FOR_INPUT || 
			state == SUDDEN_DEATH) {
			agentTurn.setColor(sf::Color::Red); 
		} else {
			agentTurn.setColor(sf::Color::Blue); 
		}
	} else {
		if(state == WAITING_FOR_CLICK || state == WAITING_FOR_INPUT || 
			state == SUDDEN_DEATH) {
			agentTurn.setColor(sf::Color::Blue); 
		} else {
			agentTurn.setColor(sf::Color::Red); 
		}	
	}
}



void GameScreen::sendHintToOtherPlayer() {
	sf::Packet codeword;
	codeword << hint << hintNum;
	if (socket->send(codeword) != sf::Socket::Done) {
	}
}

void GameScreen::waitToRecieveHintFromOtherPlayer() {
	sf::Packet codewordRecieve;
	std::string sentHint;
	int sentNum;
	if( socket->receive(codewordRecieve) == sf::Socket::Disconnected ) {
		disconnect = true;
		return;
	}
	if(codewordRecieve >> sentHint >> sentNum) {
		//numOfGuesses = sentNum+1;
		std::string newHint = sentHint + " " + std::to_string(sentNum);
		currentHint = newHint;
		currentClue.setString("Current Clue: " + newHint);
		state = WAITING_FOR_CLICK;
	}
}

//asdas
void GameScreen::waitToRecieveGuessFromOtherPlayer() {
	sf::Packet codewordRecieve;
	int cardType;
	int cardI;
	int cardJ;
	if( socket->receive(codewordRecieve) == sf::Socket::Disconnected ) {
		disconnect = true;
		return;
	}
	sf::Mutex mutex;
	if(codewordRecieve >> cardType >> cardI >> cardJ) {
		//std::cout << "Got: " << cardType << " " << cardI << " " << cardJ << std::endl;
		mutex.lock();

		switch(cardType) {
			case 0: {
				int ij25 = (cardI * 5) + cardJ;
				if(alreadyPressed.find( ij25 ) == alreadyPressed.end()) {
					alreadyPressed.insert( ij25 );
					boardPtr->boardOneColorsUI[cardI][cardJ].setColor(sf::Color::Green);
					agents++;
					agentOnBoardLeft--;
					finalTurn = false;
				}
				break;
			}
			case 1: {
				boardPtr->boardOneColorsUI[cardI][cardJ].setColor(sf::Color::Red);
				state = GAMEOVER;
				win = false;
				break;
			}
			case 2: {
				if(*isServer){
					boardPtr->boardOneColorsUI[cardI][cardJ].one = true;
				} else {
					boardPtr->boardOneColorsUI[cardI][cardJ].two = true;
				}
				if(suddenDeath) {
					std::cout << "END THIS MOTHER FUCKER" << std::endl;
					state = GAMEOVER;
					win = false;
					return;
				}

				state = WAITING_FOR_HINT;
				turns--;
				break;
			}
			case 3: {
				turns--;
				state = WAITING_FOR_HINT;
				break;
			}
		}
		mutex.unlock();
		codewordRecieve.clear();
	}
}




void GameScreen::waitForInput(sf::RenderWindow & window, char inputUnicode,
	 std::string& input) {
	if((inputUnicode == 10 || inputUnicode == 13) && (input != "")) {//Ret
		printDebug("Entered " + input);
		*(inputItem.inputStr) = input;
		hint = input;
		input = "";
		inputItem.inputText.setString("");
		inputItem.updateCursor();
			sf::Packet codeword;
		codeword << hint << hintNum;
		if (socket->send(codeword) != sf::Socket::Done) {
		}
		sf::Mutex mutex;
		mutex.lock();
		state = WAITING_FOR_GUESS;
		mutex.unlock();
	} else if (inputUnicode == 8) { //Back Space
		input = input.substr(0, input.size()-1);
		inputItem.inputText.setString(input);
        inputItem.updateCursor();
		updateScreen(window);
	} else if(inputUnicode >= '1' && inputUnicode <= '9') { //Numbers
		allHintNumbers[hintNum].setColor(sf::Color(16,117,24,255));
		int numToChange = inputUnicode - '0';
		hintNum = numToChange;
	} else { //normal chars
		if(inputItem.validateInput(inputUnicode) && input.length() <
			inputItem.maxChar && inputUnicode != '0') {
		char characterTyped = static_cast<char>(inputUnicode);
        input += characterTyped;
        inputItem.inputText.setString(input);
        inputItem.updateCursor();
		updateScreen(window);
		}	
	}
}

void GameScreen::checkForAllClicks(sf::RenderWindow & window, bool guessing) {
	sf::Packet endGuessPacket;
	endGuessPacket << 3 << 10 << 10;

	if(guessing) {
		if(endTurnButton.checkClick(window)) {
			state = WAITING_FOR_INPUT;
			socket->send(endGuessPacket);
			return;
		}

		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5;++j) {
				if(boardPtr->boardOneColorsUI[i][j].checkClick(window)) {
					int ij25 = (i * 5) + j;
					sf::Packet cardColorPacket;
					cardColorPacket << boardPtr->boardTwoStructure[i][j] <<  i << j;
					socket->send(cardColorPacket);
					cardColorPacket.clear();
					switch(boardPtr->boardTwoStructure[i][j]){
						case 0: {
							if(alreadyPressed.find( ij25 ) == alreadyPressed.end()) {
								alreadyPressed.insert( ij25 );
								if(suddenDeath) {
									agents++;
									boardPtr->boardOneColorsUI[i][j].setColor(sf::Color::Green);
								} else {
									agents++;
									boardPtr->boardOneColorsUI[i][j].setColor(sf::Color::Green);
									// --numOfGuesses;
									// if(numOfGuesses == 0) {
									// 	socket->send(endGuessPacket);
									// 	state = WAITING_FOR_INPUT;
									// 	turns--;
									// 	break;
									// }	
								}
								opponentsAgentsLeft--;
								break;
							} else {
								break;
							}

						}
						case 1: {
							boardPtr->boardOneColorsUI[i][j].setColor(sf::Color::Red);
							state = GAMEOVER;
							win = false;
							break;
						}
						case 2: {
							if(*isServer){
								boardPtr->boardOneColorsUI[i][j].two = true;
							} else {
								boardPtr->boardOneColorsUI[i][j].one = true;
							}

							if(suddenDeath) {
								std::cout << "trying to end game" << std::endl;
								state = GAMEOVER;
								win = false;
								sf::Packet endgamePacket;
								endgamePacket << 1 << 10 << 10;
								socket->send(endgamePacket);
								break;
							}
							state = WAITING_FOR_INPUT;
							turns--;
							break;
						}
					}
				}
			}
		}
	} else {
		for(int i = 0; i < 10; i++) {
			if(allHintNumbers[i].checkClick(window)) {
				allHintNumbers[hintNum].setColor(sf::Color(16, 117, 24, 255));
				hintNum = i;
			}
		}
	}
}



int GameScreen::run(sf::RenderWindow & window) {
	if(!setUpDone) {
		sf::Thread thread(&GameScreen::setUpBoardsMyBoi, this);
		printDebug("Launching Thread Baby!");
		thread.launch();
		thread.wait();
		thread.terminate();	
		setUpDone = true;
		printDebug("Terminating this thread like BUG!");
		printDebug("Opponents Name is: " + opponentName);
	}

	sf::Thread suddenDeathThread(&GameScreen::waitToRecieveGuessFromOtherPlayer, this);
	int prevState;
	updateScreen(window);
	std::string input = "";
	while(window.isOpen()) {
		updateScreen(window);
		inputItem.updateCursor();
		sf::Event e;

		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed || disconnect) {
				printDebug("TERMINATING WINDOW!");
				socket->disconnect();
				suddenDeathThread.terminate();
				return DISCONNECT;
			} 
			if(agents == 15) {
				win = true;
				state = GAMEOVER;
			}
			if(turns == 0 && !suddenDeath) {
				win = false;
				prevState = state;
				state = SUDDEN_DEATH;
				suddenDeath=true;

			}
			switch(state) {
				case WAITING_FOR_INPUT: { //Oringally Client
					socket->setBlocking(true);
					if (e.type == sf::Event::TextEntered) {
						waitForInput(window, e.text.unicode, input);
					} else 	if (e.type == sf::Event::MouseButtonPressed) {
						checkForAllClicks(window,false);
					}
					break;
				} 

				case WAITING_FOR_HINT: { //Originally Server!
					socket->setBlocking(false);
					waitToRecieveHintFromOtherPlayer();
					break;
				}
				case WAITING_FOR_CLICK: {
					socket->setBlocking(true);
					if (e.type == sf::Event::MouseButtonPressed) {
						checkForAllClicks(window,true);
					}
					break;
				}
				case WAITING_FOR_GUESS: {
					socket->setBlocking(false);
					waitToRecieveGuessFromOtherPlayer();
					break;
				}	
				case GAMEOVER: {
					socket->setBlocking(true);
					if(!finalTurn) {
						finalTurn = true;
						printDebug("Launching Final Thread!");
						suddenDeathThread.launch();
					}
					break;
				}				
				case SUDDEN_DEATH: {
					socket->setBlocking(true);
					
					if(!finalTurn) {
						finalTurn = true;
						printDebug("Launching Final Thread!");
						suddenDeathThread.launch();
					}

					//numOfGuesses = agentOnBoardLeft;
					if (e.type == sf::Event::MouseButtonPressed) {
						checkForAllClicks(window,true);
					}
				}
			}
		}
	}

	return DISCONNECT;
}










// void GameScreen::waitToRecieveGuessFromOtherPlayer() {
// 	sf::Packet codewordRecieve;
// 	std::string sentHint;
// 	int sentNum;
// 	socket->receive(codewordRecieve);
// 	if(codewordRecieve >> sentHint) {
// 		state = WAITING_FOR_CLICK_Gues;
// 	}
// }

	// if(*isServer){
	// 	boardPtr->drawMiniColorBoard(window, 2); //Is
	// } else {
	// 	boardPtr->drawMiniColorBoard(window, 1);
	// }

	// if(state == WAITING_FOR_HINT || state == WAITING_FOR_GUESS) { //Inactive Really
	// 	agentTurn.setTextItems("Agent: " + opponentName + "'s Turn" , sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/10),
	// 		(*isServer) ? sf::Color::Red : sf::Color::Blue, 48);
	// } else { //Actually your turn!
	// 	agentTurn.setTextItems("Agent: " + *username + "'s Turn" , sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/10),
	// 		(*isServer) ? sf::Color::Red : sf::Color::Blue, 48);
	// }