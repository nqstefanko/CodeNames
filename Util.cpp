#include "Util.hpp"

extern const int WINDOW_WIDTH = 1600;
extern const int WINDOW_HEIGHT = 900;
extern const int FPS = 1600;
extern const bool  DEBUG = false;

void printDebug(std::string s) {
	if(DEBUG) {
		std::cout << s << std::endl;
	}
}