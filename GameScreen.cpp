#include "GameScreen.hpp"

GameScreen::GameScreen(Board & newBoard,std::string & inputString, bool & userType,
	std::string user, sf::TcpSocket & sock):
	inputItem(inputString), 
	turnsLeft("Turns:9", sf::Vector2f(WINDOW_WIDTH/1.25, WINDOW_HEIGHT/1.5), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" ),
	agentsLeft("Agents:15", sf::Vector2f(WINDOW_WIDTH/1.25, WINDOW_HEIGHT/1.75), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" ),
	agentTurn("Agent: " + user + "'s Turn" , sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/10), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" ),
	agentName(user, sf::Vector2f(WINDOW_WIDTH/40, WINDOW_HEIGHT/30), sf::Color::White, 48, 
		"fonts/Xpressive Regular.ttf" )
	
{
	isServer = &userType;
	boardPtr = &newBoard;
	username = &user;
	socket = &sock;
	setUpDone= false;
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
	turnsLeft.draw(window);
	agentsLeft.draw(window);
	agentTurn.draw(window);
	//agentName.draw(window);
	codenamesLogo.draw(window);
	inputItem.updateScreen(window);
    window.display();
}

void GameScreen::setUpBoardsMyBoi() {
	sf::Packet packetWord;
	sf::Packet packetBoard;
	

	
	std::set<std::string> newWords;
	std::string boardStr;
	std::string currentWord;


	if(*isServer) {//SERVER SIDE!!
		std::string s;
		int i;
		int count = 0;
		sf::Packet packetWordRecieve;

		while(newWords.size() != 25) {
			sf::Packet packetBoardRecieve;
			socket->receive(packetWordRecieve);
			if (packetWordRecieve >> s >> i)
			{
			    std::cout << s << i << std::endl;
			    if(newWords.find(s) == newWords.end()) { //if not in bro
				    newWords.insert(s);
				    boardPtr->words[i] = s;
			    }
			    packetWordRecieve.clear();
			}			
		}
		printDebug("Getting Board");
		s = "";
		socket->receive(packetWordRecieve);
		if (packetWordRecieve >> s)
		{
		    std::cout << s << std::endl;
			boardPtr->setBoard(s);
		}

	} else {//CLIENT SIDE
		packetBoard << boardPtr->getBoardValues(2);
		for(int i = 0; i < 25;i++) {
			printDebug("Sending on ClientSide " + boardPtr->words[i] + " " + std::to_string(i));
			packetWord << boardPtr->words[i] << i;
			if (socket->send(packetWord) != sf::Socket::Done)
			{
			    printDebug("Fuck error");
			}
			packetWord.clear();

		}
		printDebug("Sending PB: " + boardPtr->getBoardValues(2));
		socket->send(packetBoard);
		return;
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
	}

	std::string input;
	while(window.isOpen()) {
		updateScreen(window);
		inputItem.updateCursor();
		sf::Event e;
		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) {
				printDebug("Closing Input String");
				window.close();
				return -1;
			} else if (e.type == sf::Event::MouseButtonPressed)
			{
				printDebug("Clicked Something man");

			} else if (e.type == sf::Event::TextEntered) {
				if(e.text.unicode == 10 || e.text.unicode == 12 || e.text.unicode == 13) {//Ret
					printDebug("Entered " + input);
					*(inputItem.inputStr) = input;
					input = "";
					inputItem.inputText.setString("");
				} else if (e.text.unicode == 8) { //Back Space
					input = input.substr(0, input.size()-1);
					inputItem.inputText.setString(input);
                    inputItem.updateCursor();
					updateScreen(window);
				} else {
					if(inputItem.validateInput(e.text.unicode) && input.length() < inputItem.maxChar) {
					char characterTyped = static_cast<char>(e.text.unicode);
                    input += characterTyped;
                    inputItem.inputText.setString(input);
                    inputItem.updateCursor();
					updateScreen(window);
					}	
				}
			}
		}
	}

	return -1;
}