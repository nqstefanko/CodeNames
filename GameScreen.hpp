#ifndef GAMESCREEN_H
#define GAMESCREEN_H


#define WAITING_FOR_INPUT 100
#define WAITING_FOR_HINT 101
#define WAITING_FOR_CLICK 102
#define WAITING_FOR_GUESS 103
#define SUDDEN_DEATH 104
#define GAMEOVER 105

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include <set>
#include <vector>

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
	std::string opponentName;
	std::string hint;
	std::string currentHint;

	std::vector<Button> allHintNumbers;
	std::vector<std::string> allWords;
	std::vector<int> positions;
	std::vector<int> filledIn;

	std::set<std::string> currentWords;
	int hintNum;
	int numOfGuesses;
	int turns;
	int agents;
	int agentOnBoardLeft;
	int state = 0;

	bool * isServer; 
	bool opponenetsMove;
	bool setUpDone;
	bool win;
	bool suddenDeath;
	bool finalTurn;


	Board * boardPtr;
	sf::TcpSocket * socket;
	InputBox inputItem;

	Text turnsLeft;
	Text agentsLeft;
	Text agentTurn;
	Text currentClue;
	Text guessText;

	Button endTurnButton;

	void setUpBoardsMyBoi();
	void sendHintToOtherPlayer();
	void waitToRecieveHintFromOtherPlayer();
	void waitToRecieveGuessFromOtherPlayer();

	void waitForInput(sf::RenderWindow & window, char inputUnicode, std::string& input);
	void checkForAllClicks(sf::RenderWindow & window, bool guessing);
	void makeActionText();

    GameScreen(Board & newBoard,std::string & inputString, bool & userType,
	std::string &user, sf::TcpSocket & sock);
    virtual int run(sf::RenderWindow & window);
};

#endif // CHOOSINGSCREEN_H