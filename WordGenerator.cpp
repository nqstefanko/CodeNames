#include "WordGenerator.hpp"

WordGenerator::WordGenerator(std::string filename) {
    std::ifstream inFile;
    std::string word;

    inFile.open(filename.c_str());
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (inFile >> word) {
        allWords.push_back(word);
    }
    
    inFile.close();
}


std::vector<std::string> WordGenerator::generateWords(int numberOFWords) {
	std::set<std::string> currentGameWords;
	std::random_device device;


	std::default_random_engine engine{device()};


	std::uniform_int_distribution<int> distribution{0, (int)(allWords.size())};


	while((int)(currentGameWords.size()) < numberOFWords) {
		currentGameWords.insert(allWords[distribution(engine)]);
	}
	
	std::vector<std::string> toRet(numberOFWords);
	std::copy(currentGameWords.begin(), currentGameWords.end(), toRet.begin());
	return toRet;
}