
# Codenames: main.cpp Button.cpp ButtonActions.cpp Text.cpp 
# 	clang++-7 -std=c++11 main.cpp Button.cpp ButtonActions.cpp Text.cpp OpeningScreen.cpp -o Codenames -lsfml-graphics -lsfml-window -lsfml-system -pthread

Compile: main.cpp Util.cpp Text.cpp InputScreen.cpp
	clang++-7 -c -std=c++11 main.cpp Util.cpp Text.cpp InputScreen.cpp -I /home/nick/SFML-2.5.1/include

Link: main.cpp Text.cpp InputScreen.cpp
	clang++-7 main.o Util.o Text.o InputScreen.o -o Codenames -L /home/nick/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system

Codenames:
	make Compile
	make Link

# Codenames: ERROR
# 	clang++-7 main.cpp InputScreen.cpp -L /home/nick/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system 

PackageManCodenames:
	clang++ main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system


Clean:
	rm Codenames
