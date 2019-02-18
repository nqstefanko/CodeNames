#ifndef CONNECTIONSCREEN_H
#define CONNECTIONSCREEN_H

#include <SFML/Network.hpp>

#include <string>
#include <iostream>
//#include <vector>

#include "CScreen.hpp"
#include "Text.hpp"
#include "Util.hpp"

class ConnectionScreen : public CScreen {
private:
	sf::TcpSocket * clientSocket;
	sf::TcpListener listener;
	sf::TcpSocket acceptingSocket;
	std::string ipAddress;
	std::string * username;
	Text theText;
	bool * isServer; 
	bool connected;
	void makeConnection();
	void updateScreen(sf::RenderWindow & window);

public:
    ConnectionScreen(bool & isThisTheServer, sf::TcpSocket & socket,std::string & user);
    virtual int run(sf::RenderWindow & window);
};

#endif // CONNECTIONSCREEN_H