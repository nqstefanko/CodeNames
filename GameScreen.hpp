#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <string>
#include <iostream>
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
	bool * isServer; 
	Board * boardPtr;
	sf::TcpSocket * socket;
	InputBox inputItem;
	Text turnsLeft;
	Text agentsLeft;
    GameScreen(Board & board,std::string & inputString, bool & userType);
    virtual int run(sf::RenderWindow & window);
};

#endif // CHOOSINGSCREEN_H