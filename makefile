# Codenames: Utils.cpp main.cpp Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp OpeningScreen.cpp PlayBoardScreen.cpp SpyMasterBoardScreen.cpp
# 	clang++-7 -std=c++11 main.o -o Codenames -lsfml-graphics -I/home/nick/sfml2build/sfml2src/include -lsfml-window -lsfml-system -pthread
# Compile: Utils.cpp main.cpp Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp OpeningScreen.cpp PlayBoardScreen.cpp SpyMasterBoardScreen.cpp
# 	clang++-7 -c -std=c++14 Utils.cpp main.cpp  Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp SpyMasterBoardScreen.cpp OpeningScreen.cpp PlayBoardScreen.cpp -I/home/nick/sfml2build/include

Codenames: Utils.cpp main.cpp Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp OpeningScreen.cpp PlayBoardScreen.cpp SpyMasterBoardScreen.cpp
	clang++-7 -std=c++11 Utils.cpp main.cpp  Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp SpyMasterBoardScreen.cpp OpeningScreen.cpp PlayBoardScreen.cpp -o Codenames -lsfml-graphics -lsfml-window -lsfml-system -pthread
clean:
	rm Codenames