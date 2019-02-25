#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>

#include "Text.hpp"
#include "Util.hpp"


class InputBox {
public:
    std::string *inputStr, queryMsg;
    sf::RectangleShape inputRect, cursor;
    Text inputText, queryText;
    int maxChar;

    InputBox(std::string & inputString, std::string queryMessage="Input Codeword", int maxCharacter=24);
    void updateCursor();
    void initInputComponents();
    void initTextComponents();
    bool validateInput(int asciiId);
    void updateScreen(sf::RenderWindow & window);

};

#endif // INPUTBOX_H