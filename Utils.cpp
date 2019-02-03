// #include "Utils.hpp"

// void Utils::closeItAll(sf::RenderWindow &app) {
// 	app.close();
// 	exit(0);
// }
#ifndef UTILS
#define UTILS

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

namespace Utils {
	void closeItAll(sf::RenderWindow &app) {
		app.close();
		exit(0);
}
};

#endif