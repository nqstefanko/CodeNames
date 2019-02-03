Codenames: Utils.cpp main.cpp Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp OpeningScreen.cpp PlayBoardScreen.cpp SpyMasterBoardScreen.cpp
	clang++ -std=c++11 Utils.cpp main.cpp  Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp SpyMasterBoardScreen.cpp OpeningScreen.cpp PlayBoardScreen.cpp -o Codenames -lsfml-graphics -lsfml-window -lsfml-system -pthread
clean:
	rm Codenames