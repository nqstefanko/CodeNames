#ifndef CHOOSINGSCREEN_H
#define CHOOSINGSCREEN_H


#include <string>
#include <iostream>
//#include <vector>

#include "CScreen.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include "Button.hpp"

class ChoosingScreen : public CScreen {
private:
	bool * isServer; 
	void updateScreen(sf::RenderWindow & window, std::vector<Button> & allButtons);

public:
    ChoosingScreen(bool & userType);
    virtual int run(sf::RenderWindow & window);
};

#endif // CHOOSINGSCREEN_H