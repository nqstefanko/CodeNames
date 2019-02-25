#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include <set>
//#include <vector>

#include "CScreen.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include "Button.hpp"
#include "Board.hpp"
#include "InputBox.hpp"

class GameScreen : public CScreen {
private:
	void updateScreen(sf::RenderWindow & window);
	
public:

	std::string *username;
	bool opponenetsMove;
	bool * isServer; 
	bool setUpDone;
	Board * boardPtr;
	sf::TcpSocket * socket;
	InputBox inputItem;

	Text turnsLeft;
	Text agentsLeft;
	Text agentTurn;
	Text agentName;

	void setUpBoardsMyBoi();
    GameScreen(Board & newBoard,std::string & inputString, bool & userType,
	std::string user, sf::TcpSocket & sock);
    virtual int run(sf::RenderWindow & window);
};

#endif // CHOOSINGSCREEN_H