#include "Util.hpp"

extern const int WINDOW_WIDTH = 1600;
extern const int WINDOW_HEIGHT = 900;
extern const int FPS = 60;
extern const bool  DEBUG = false;
extern const int CLIENT_USER = 0;
extern const int SERVER_USER = 1;
extern const int INPUT_SCREEN = 0;
extern const int CHOOSE_SCREEN = 1;
extern const int CONN_SCREEN = 2;
extern const int GAMESCREEN_SCREEN = 3;
extern const int DISCONNECT = -1;
extern const std::string FONTF = "fonts/Xpressive Regular.ttf";
extern const int AGENT = 0;
extern const int ASSASSIN = 1;
extern const int BYSTANDER = 2;

sf::Vector2f getV2f(float x, float y, bool divByWindow) {
	if(divByWindow) {
		return sf::Vector2f(WINDOW_WIDTH/x, WINDOW_HEIGHT/y);
	} else {
		return sf::Vector2f(x, y);
	}
} 
void printDebug(std::string s) {
	if(DEBUG) {
		std::cout << s << std::endl;
	}
}
void printBoard(std::vector<std::vector<int>> board) {
	for(int i = 0; i < 5; ++i) {
		std::cout << "[";
		for(int j = 0; j < 5; ++j) {
			std::cout << board[i][j] << ", ";
		}
		std::cout << "]"<<std::endl;
	}
}

void printVector(std::vector<int> v) {
	for(int i = 0; i < v.size(); ++i) {
		std::cout << v[i]<< " " <<std::endl;
	}
	std::cout << std::endl;
}
