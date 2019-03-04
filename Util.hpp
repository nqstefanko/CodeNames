#ifndef UTIL_H
#define UTIL_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

extern const int WINDOW_WIDTH; 
extern const int WINDOW_HEIGHT;
extern const int FPS;
extern const bool DEBUG;
extern const int CLIENT_USER;
extern const int SERVER_USER;

extern const int CONN_SCREEN;
extern const int INPUT_SCREEN;
extern const int CHOOSE_SCREEN;
extern const int GAMESCREEN_SCREEN;
extern const int DISCONNECT;

extern const std::string FONTF;

extern const int ASSASSIN;
extern const int AGENT;
extern const int BYSTANDER;

sf::Vector2f getV2f(float x, float y, bool divByWindow = false);
void printDebug(std::string s);
void printBoard(std::vector<std::vector<int>> board);
void printVector(std::vector<int> v);

#endif
