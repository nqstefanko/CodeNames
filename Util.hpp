#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>

extern const int WINDOW_WIDTH; 
extern const int WINDOW_HEIGHT;
extern const int FPS;
extern const bool DEBUG;
extern const int CLIENT_USER;
extern const int SERVER_USER;
extern const int ASSASSIN;
extern const int AGENT;
extern const int BYSTANDER;


void printDebug(std::string s);
void printBoard(std::vector<std::vector<int>> board);
void printVector(std::vector<int> v);

#endif
