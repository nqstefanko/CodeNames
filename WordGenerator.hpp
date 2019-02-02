#ifndef WORD_GENERATOR
#define WORD_GENERATOR

#include <iostream>
#include <functional>
#include <vector>
#include <set>
#include <fstream>
#include <iomanip>
#include <random>


class WordGenerator {
public:
	WordGenerator(std::string filename = std::string("allCodenameWords.txt"));
	std::vector<std::string> generateWords(int numberOFWords = 25);

private:
	std::vector<std::string> allWords;

};


#endif
