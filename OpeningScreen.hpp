#ifndef OPENING_SCREEN
#define OPENING_SCREEN


#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <vector>

#include "CScreen.hpp"
#include "Button.hpp"
#include "ButtonActions.hpp"
#include "Text.hpp"



class OpeningScreen: public CScreen
{
public:
	virtual int Run(sf::RenderWindow &app);
	OpeningScreen();

private:

};

#endif