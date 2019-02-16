#ifndef CONNECTIONSCREEN_H
#define CONNECTIONSCREEN_H

#include <string>
#include <iostream>
//#include <vector>

#include "CScreen.hpp"
#include "Text.hpp"
#include "Util.hpp"

class ConnectionScreen : public CScreen {
private:
	sf::TcpSocket * socketBro;
	bool * serverOrClient; 

	void updateScreen(sf::RenderWindow & window);

public:
    ConnectionScreen(bool & userType);
    virtual int run(sf::RenderWindow & window);
};

#endif // CONNECTIONSCREEN_H