#ifndef INPUTSCREEN_H
#define INPUTSCREEN_H

#include <SFML/Network.hpp>


#include <string>
#include <iostream>

#include "CScreen.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include "InputBox.hpp"


class InputScreen : public CScreen {
private:
    InputBox inputItem;
    std::string * ipAddress;
    void updateScreen(sf::RenderWindow & window);

public:
    InputScreen(std::string & inputString, std::string & ip, 
    	std::string queryMessage, int maxCharacter);
    virtual int run(sf::RenderWindow & window);
};

#endif // INPUTSCREEN_H