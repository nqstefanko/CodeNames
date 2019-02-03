#ifndef SPY_SCREEN
#define SPY_SCREEN


#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <vector>

#include "CScreen.hpp"
#include "Button.hpp"
#include "ButtonActions.hpp"
#include "Text.hpp"



class SpyMasterBoardScreen: public CScreen
{
public:
	SpyMasterBoardScreen();
	std::vector<std::vector<int>> makeTheBoard();
	virtual int Run(sf::RenderWindow &app);

	void drawOnBoard(sf::RenderWindow &app);
	

private:

};

#endif