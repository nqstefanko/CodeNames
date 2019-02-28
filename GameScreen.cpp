#include "GameScreen.hpp"

GameScreen::GameScreen(Board & newBoard,std::string & inputString, bool & userType,
	std::string &user, sf::TcpSocket & sock):
	inputItem(inputString), 
	turnsLeft("Turns:9", sf::Vector2f(WINDOW_WIDTH/1.25, WINDOW_HEIGHT/1.5), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" ),
	agentsLeft("Agents:15", sf::Vector2f(WINDOW_WIDTH/1.25, WINDOW_HEIGHT/1.75), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" ),
	agentTurn("Agent: " + user + "'s Turn" , sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/10),
	 (userType) ? sf::Color::Red : sf::Color::Blue, 48, 
		"fonts/Xpressive Regular.ttf" ),
	currentClue("Current Clue: Waiting on Sender!", sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/30), sf::Color::Green, 48, 
		"fonts/Xpressive Regular.ttf" )
	
{
	std::cout << userType << user << std::endl;
	isServer = &userType;
	boardPtr = &newBoard;
	username = &user;
	socket = &sock;
	setUpDone= false;
	hintNum = 1;
	

	for(int i = 1; i < 10; ++i) { //Draw 1-9 Buttons
		sf::Vector2f tempButtonSize(WINDOW_WIDTH/40, WINDOW_HEIGHT/20);
		sf::Vector2f tempButtonLoc(WINDOW_WIDTH/1.35, WINDOW_HEIGHT/3.35 +((WINDOW_HEIGHT/16)+3)*i );
		Button tempBtn(std::to_string(i), tempButtonLoc, tempButtonSize,
			sf::Color(16,117,24,255), WINDOW_WIDTH/38, i+1100);
		allHintNumbers.push_back(tempBtn);
	}
}

void GameScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
	boardPtr->drawBoard(window);

	if(*isServer){
		boardPtr->drawMiniColorBoard(window, 1);
	} else {
		boardPtr->drawMiniColorBoard(window, 2);
	}

	Text codenamesLogo("Codenames Duet", sf::Vector2f(WINDOW_WIDTH/3, 0), sf::Color::Green, 42, 
		"fonts/Xpressive Regular.ttf" );

	if(state == WAITING_FOR_HINT || state == WAITING_FOR_GUESS) { //Inactive Really
		agentTurn.setTextItems("Agent: " + opponentName + "'s Turn" , sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/10),
			(*isServer) ? sf::Color::Red : sf::Color::Blue, 48);
	} else { //Actually your turn!
		agentTurn.setTextItems("Agent: " + *username + "'s Turn" , sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/10),
			(*isServer) ? sf::Color::Red : sf::Color::Blue, 48);
	}

	turnsLeft.draw(window);
	agentsLeft.draw(window);
	agentTurn.draw(window);

	for(int i = 1; i < 10; ++i) {
		allHintNumbers[i-1].draw(window); //Draw 1-9 Buttons
	}
	
	currentClue.draw(window);
	codenamesLogo.draw(window);
	inputItem.updateScreen(window);
    
    window.display();
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
		std::string s2;
		std::string s3;
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
			    if(newWords.find(s) == newWords.end()) { //if not in bro
				    newWords.insert(s);
				    boardPtr->words[i] = s;
			    }
			    packetWordRecieve.clear();
			}			
		}
		s = "";
		socket->receive(packetWordRecieve);
		if (packetWordRecieve >> s >> s2 >> s3) //Getting boards and opponent name!
		{
			boardPtr->setBoard(s, 2);
			boardPtr->setBoard(s2, 1);
			opponentName = s3;
		}

		sendName << *username;
		socket->send(sendName);
		return;

	} else {//CLIENT SIDE
		state = WAITING_FOR_INPUT;
		printDebug("CLIENT: STATE IS WAINTING FOR INPUT!!");

		packetBoard << boardPtr->getBoardValues(2);
		packetBoard << boardPtr->getBoardValues(1);
		packetBoard << *username;

		for(int i = 0; i < 25;i++) {
			//printDebug("Sending on ClientSide " + boardPtr->words[i] + " " + std::to_string(i));
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
		return;
	}
}



void GameScreen::sendHintToOtherPlayer() {
	sf::Packet codeword;
	codeword << hint << hintNum;
	if (socket->send(codeword) != sf::Socket::Done) {
	}
}

void GameScreen::waitToRecieveFromOtherPlayer() {
	sf::Packet codewordRecieve;
	std::string sentHint;
	int sentNum;
	socket->receive(codewordRecieve);
	if(codewordRecieve >> sentHint >> sentNum) {
		std::string newHint = sentHint + " " + std::to_string(sentNum);
		currentHint = newHint;
		currentClue.setString(newHint);
		state = WAITING_FOR_CLICK;
		return;
	}
}

void GameScreen::waitForInput(sf::RenderWindow & window, char inputUnicode, std::string& input) {
	if((inputUnicode == 10 || inputUnicode == 12 || inputUnicode == 13) && (input != "")) {//Ret
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
	} else if(inputUnicode >= '1' && inputUnicode <= '9') {
		allHintNumbers[hintNum].setColor(sf::Color(16,117,24,255));
		int numToChange = inputUnicode - '0';
		hintNum = numToChange-1;
		allHintNumbers[numToChange-1].setColor(sf::Color::Magenta);
	} else {
		if(inputItem.validateInput(inputUnicode) && input.length() < inputItem.maxChar && inputUnicode != '0') {
		char characterTyped = static_cast<char>(inputUnicode);
        input += characterTyped;
        inputItem.inputText.setString(input);
        inputItem.updateCursor();
		updateScreen(window);
		}	
	}
}

void GameScreen::checkForAllClicks(sf::RenderWindow & window) {
	for(int i = 0; i < 5;i++) {
		for(int j = 0; j < 5;++j) {
			if(boardPtr->boardOneColorsUI[i][j].checkClick(window)) {
				printDebug("Clicked This button Bro" + std::to_string(i) +
				 " " + std::to_string(j) );
			}
		}
	}
	for(int i = 0; i < 10;i++) {
		if(allHintNumbers[i].checkClick(window)) {
			allHintNumbers[hintNum].setColor(sf::Color(16,117,24,255));;
			hintNum = i;
			allHintNumbers[i].setColor(sf::Color::Magenta);
		}
	}
}



int GameScreen::run(sf::RenderWindow & window) {
	if(!setUpDone) {
		sf::Thread thread(&GameScreen::setUpBoardsMyBoi, this);
		printDebug("Luanching Thread Baby!");
		thread.launch();
		thread.wait();
		thread.terminate();	
		setUpDone = true;
		printDebug("Terminating this thread like BUG!");
		printDebug("Opponents Name is: " + opponentName);
	}

	updateScreen(window);
	std::string input = "";
	while(window.isOpen()) {
		updateScreen(window);
		inputItem.updateCursor();
		sf::Event e;

		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) {
				printDebug("TERMINATING WINDOW!");
				window.close();
				return -1;
			} 
			switch(state) {
				case WAITING_FOR_INPUT: { //Oringally Client
					if (e.type == sf::Event::TextEntered) {
						waitForInput(window, e.text.unicode, input);
					}
					break;
				} 

				case WAITING_FOR_HINT: { //Originally Server!
					sf::Thread thread(&GameScreen::waitToRecieveFromOtherPlayer, this);
					thread.launch();
					printDebug("LAUCHED WAIT THREAD");
					thread.wait();
					thread.terminate();
					printDebug("TERMINATED THREAD");
					break;
				}
				case WAITING_FOR_CLICK: {
					if (e.type == sf::Event::MouseButtonPressed) {
						checkForAllClicks(window);
					}
					break;
				}
				case WAITING_FOR_GUESS:break; 
			}
		}
	}

	return -1;
}