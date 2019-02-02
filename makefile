Codenames: main.cpp
	clang++ -std=c++11 main.cpp OpeningScreen.cpp Button.cpp ButtonActions.cpp Text.cpp WordGenerator.cpp PlayBoardScreen.cpp -o Codenames -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm Codenames