#include "Util.hpp"

extern const int WINDOW_WIDTH = 800;
extern const int WINDOW_HEIGHT = 600;
extern const int FPS = 60;
extern const bool  DEBUG = true;
extern const int CLIENT_USER = 0;
extern const int SERVER_USER = 1;

void printDebug(std::string s) {
	if(DEBUG) {
		std::cout << s << std::endl;
	}
}