#ifndef BOARD_H
#define BOARD_H

#include "Button.hpp"
#include "WordGenerator.hpp"
#include "Util.hpp"

class Board
{
public:///0 is green, 1 is assassin, 2 is neutral
	Board();//Need 111111111 and words. Can send both
	std::vector<std::vector<int>> generate5x5Board();
	std::vector<std::vector<int>> generateOpposingBoard();
	void generateBoards();
	void setBoard(std::string allBoardValues, int boardNumber);
	void setWords(std::string newWord, int num);
	void makeBoardUI();
	void drawBoard(sf::RenderWindow & window);

	void drawMiniColorBoard(sf::RenderWindow & window, int boardNumber);
	void showSpyBoard(sf::RenderWindow & window);
	std::string getBoardValues(int num);
	std::vector<std::string> words;
	
	std::map<int, std::vector<int>> teamBreakdown;
	std::map<int, std::vector<int>> opponentBreakdown;

	std::vector<std::vector<int>> boardOneStructure;
	std::vector<std::vector<int>> boardTwoStructure;
	std::vector<std::vector<Button>> boardOneColorsUI;

	
	WordGenerator generator;

};

#endif