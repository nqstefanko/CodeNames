#ifndef INPUTSCREEN_H
#define INPUTSCREEN_H

#include <SFML/Network.hpp>


#include <string>
#include <iostream>

#include "CScreen.hpp"
#include "Text.hpp"
#include "Util.hpp"


class InputScreen : public CScreen {
private:
    std::string *inputStr, queryMsg;
    std::string * ipAddress;
    sf::RectangleShape inputBox, cursor;
    Text inputText, queryText;
    int maxChar;
    void setInputStr(std::string & newStr);
    void initInputComponents();
    void initTextComponents();
    bool validateInput(int asciiId);
    void updateCursor();
    void updateScreen(sf::RenderWindow & window);

public:
    InputScreen(std::string & inputString, std::string & ip, std::string queryMessage, int maxCharacter);
    virtual int run(sf::RenderWindow & window);
};

#endif // INPUTSCREEN_H