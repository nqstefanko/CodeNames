#ifndef C_SCREEN
#define C_SCREEN

#include <SFML/Graphics.hpp>


class CScreen 
{
public:
	virtual int run(sf::RenderWindow & app) = 0; 
	
};

#endif