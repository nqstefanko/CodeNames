#include "Util.hpp"

extern const int WINDOW_WIDTH = 1600;
extern const int WINDOW_HEIGHT = 900;
extern const int FPS = 60;
extern const bool  DEBUG = true;
extern const int CLIENT_USER = 0;
extern const int SERVER_USER = 1;

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
