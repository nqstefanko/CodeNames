#include "ConnectionScreen.hpp"

ConnectionScreen::ConnectionScreen(bool & isThisTheServer, sf::TcpSocket & socket,
	std::string & user){
	isServer = &isThisTheServer;
	clientSocket = &socket;
	username = &user;
	connected = false;
}

void ConnectionScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
    window.display();
}

void ConnectionScreen::makeConnection() {
	sf::Packet packet;
	std::string s;
	if(*isServer) {//SERVER SIDE!!
		printDebug("Listening...");
		if(listener.listen(6969) != sf::Socket::Done) {
			printDebug("Fuck Boss we got a Listening error!");
			return;
		}

		if(listener.accept(*clientSocket) != sf::Socket::Done ) {
			printDebug("TITS Boss we got an Acceptance error!");
			return;
		}
		printDebug("Connected from SERVER");
		connected = true;
		packet << "Server: Welcome " + *username;
		clientSocket->send(packet);
		clientSocket->receive(packet);
		if (packet >> s)
		{
		    std::cout << s << std::endl;
		}
		else
		{
		    printDebug("Cunt 1");
		}

	} else {//CLIENT SIDE
		printDebug("Trying to Connect to Server!");
		sf::Socket::Status status = clientSocket->connect("127.0.0.1", 6969);
		if (status != sf::Socket::Done)
		{
			printDebug("Status Error Client!");
			return;

		}
		printDebug("Connected From CLIENT");
		connected = true;
		packet << "Client: Welcome " + *username;
		
		clientSocket->send(packet);
		clientSocket->receive(packet);
		if (packet >> s)
		{
		    std::cout << s << std::endl;
		}
		else
		{
		    printDebug("Cunt 2");
		}
	}

}

int ConnectionScreen::run(sf::RenderWindow & window) {
	sf::Thread thread(&ConnectionScreen::makeConnection, this);
	thread.launch();

	while(window.isOpen()) {
		updateScreen(window);

		sf::Event e;
		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) {
				printDebug("Closing Input String");
				window.close();
				return -1;
			} 
			if(connected) {
				return 3;
			}
		}
	}
	return -1;
}