#ifndef BOARD_H
#define BOARD_H

#include "Button.hpp"
#include "WordGenerator.hpp"

class Board
{
public:
	Board();
	void generateBoards();
private:
	std::vector<std::vector<Button>> boardOneUI;
	std::vector<std::vector<Button>> boardTwoUI;

	std::vector<std::vector<int>> boardOneStructure;
	std::vector<std::vector<int>> boardTwoStructure;
	
	WordGenerator generator;

};

#endif