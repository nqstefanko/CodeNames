#ifndef PLAY_BOARD_SCREEN
#define PLAY_BOARD_SCREEN


#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <vector>

#include "CScreen.hpp"
#include "OpeningScreen.hpp"

#include "Button.hpp"
#include "ButtonActions.hpp"
#include "Text.hpp"
#include "WordGenerator.hpp"



class PlayBoardScreen: public CScreen
{
public:
	virtual int Run(sf::RenderWindow &app);
	PlayBoardScreen();

private:

};

#endif