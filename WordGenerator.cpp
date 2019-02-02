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
	// Creates an object that lets us tap into our source of entropy.  Note
	// that we only want to do this once and then use it sparingly.  Once created,
	// the device can be called like a function.
	std::random_device device;

	// Now that we want to generate a pseudorandom sequence of bits, we seed a
	// random engine using our random_device.  While we wouldn't want to use the
	// random_device over and over again, we can use it to seed a pseudorandom
	// generator, and then let the algorithm's properties of seeming randomness
	// take over from there.
	std::default_random_engine engine{device()};

	// Finally, we need a distribution, so we can specify what kinds of values we
	// actually want.  A uniform_int_distribution is one that generates integer
	// values between a given minimum and maximum (inclusive), so, for example,
	// the one below generates values between 1 and 6 (inclusive), with each of
	// those possible values being equally likely.
	std::uniform_int_distribution<int> distribution{0, (int)(allWords.size())};

	// Now that we have all of the pieces set up, we're ready to generate our
	// sequence of die rolls.  Notice that the distribution can also be called
	// like a function whenever we want our next value, and that we pass the
	// engine as a parameter.  When the distribution needs more pseudorandom
	// bits, it asks the engine for them, so we don't have to worry about that
	// part of it; we simply say "Give us numbers between 1 and 6" and we'll
	// get a non-biased, uniformly-distributed sequence of numbers.
	while((int)(currentGameWords.size()) < numberOFWords) {
		currentGameWords.insert(allWords[distribution(engine)]);
	}
	std::vector<std::string> toRet(numberOFWords);
	std::copy(currentGameWords.begin(), currentGameWords.end(), toRet.begin());
	return toRet;
}