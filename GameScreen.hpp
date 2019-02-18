#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <string>
#include <iostream>
//#include <vector>

#include "CScreen.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include "Button.hpp"

class GameScreen : public CScreen {
private:
	void updateScreen(sf::RenderWindow & window);
	
public:
    GameScreen();
    virtual int run(sf::RenderWindow & window);
};

#endif // CHOOSINGSCREEN_H