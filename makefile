Codenames: Utils.cpp main.cpp Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp OpeningScreen.cpp PlayBoardScreen.cpp
	clang++ -std=c++11 Utils.cpp main.cpp  Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp OpeningScreen.cpp PlayBoardScreen.cpp -o Codenames -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm Codenames