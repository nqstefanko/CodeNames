#include "ConnectionScreen.hpp"

ConnectionScreen::ConnectionScreen(bool & isThisTheServer, sf::TcpSocket & socket,
	std::string & user, std::string ip):
	theText("Awaiting Connection...", getV2f(3, 3, true), sf::Color::White, 48, 
		FONTF )
	{
	count = 0;
	isServer = &isThisTheServer;
	clientSocket = &socket;
	username = &user;
	connected = false;
	if(ip == ""){
		ipAddress="127.0.0.1"; //For Testing, so do not have to type in every time
	} else {
		ipAddress = ip;

	}
}

void ConnectionScreen::updateScreen(sf::RenderWindow & window) {
	window.clear(sf::Color::Black);
	theText.draw(window);
	sf::RectangleShape line(sf::Vector2f(100.f, 5.f));
	sf::CircleShape circle(100.f);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(getV2f(2.62, 2.17, true));
	line.setPosition(getV2f(2.25, 1.75, true));
	line.rotate((float)count);
	++count;
	if(count == 360) {
		count = 0;
	}
	window.draw(circle);
	window.draw(line);
    window.display();
}

void ConnectionScreen::makeConnection() {
	sf::Packet packet;
	std::string s;
	if(*isServer) {//SERVER SIDE!!
		printDebug("Listening...");
		if(listener.listen(6969) != sf::Socket::Done) {
			printDebug("Darn Boss we got a Listening error!");
			return;
		}

		if(listener.accept(*clientSocket) != sf::Socket::Done ) {
			printDebug("Shoot Boss we got an Acceptance error!");
			return;
		}
		printDebug("Connected from SERVER");
		connected = true;
	} else {//CLIENT SIDE
		printDebug("Trying to Connect to Server!");
		sf::Socket::Status status = clientSocket->connect(ipAddress, 6969);
		if (status != sf::Socket::Done)
		{
			printDebug("Status Error Client!");
			return;
		}
		printDebug("Connected From CLIENT");
		connected = true;
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
				thread.terminate();
				return DISCONNECT;
			}
			if(connected) {
				return GAMESCREEN_SCREEN;
			}
		}
	}
	return -1;
}











// packet << "Client: Welcome " + *username;
		
// 		clientSocket->send(packet);
// 		clientSocket->receive(packet);
// 		if (packet >> s)
// 		{
// 		    std::cout << s << std::endl;
// 		}
// 		else
// 		{
// 		    printDebug("Cunt 2");
// 		}

// packet << "Server: Welcome " + *username;
// clientSocket->send(packet);
// clientSocket->receive(packet);
// if (packet >> s)
// {
//     std::cout << s << std::endl;
// }
// else
// {
//     printDebug("Packets Not Sent 1");
// }