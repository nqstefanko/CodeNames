Codenames: main.cpp
	clang++ main.cpp OpeningScreen.cpp Button.cpp ButtonActions.cpp Text.cpp -o Codenames -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm Codenames