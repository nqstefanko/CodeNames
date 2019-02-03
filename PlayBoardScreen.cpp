#include "PlayBoardScreen.hpp"
#include <thread>
#include <SFML/System.hpp>


PlayBoardScreen::PlayBoardScreen(){}

void closeItAllNow(sf::RenderWindow &app) {
	app.close();
	exit(0);
}

void spawn()
{
	//SpyMasterBoardScreen smbs;
	for (int i = 0; i < 10; ++i)
        std::cout << "I'm thread number one" << std::endl;
    sf::Event event;
    sf::RenderWindow w(sf::VideoMode(400, 400), "tits" );
    //w.setActive(true);
    
    //smbs.drawOnBoard(w);

    while (w.isOpen())
    {
    	std::cout << "fa";
        while (w.pollEvent(event))
            if (event.type == sf::Event::Closed) {
            	w.close();
            	return;
            }


        w.display();
        w.clear();
    }
        
}
// void openSpyMasterBoard(sf::RenderWindow &app) {
// 	std::thread(&spawn , "WINDOW #2" ).detach();

// 	// SpyMasterBoardScreen smbs;
// 	// int temp = 2;
// 	// while(temp > 0) {
// 	// 	temp = smbs.Run(app);
// 	// }

// }




int PlayBoardScreen::Run(sf::RenderWindow &app) {
	std::vector<std::vector<Button>> allCodeNames;
	WordGenerator codeDict("allCodenameWords.txt");
	int count = 0;
	sf::Event event;
	bool running = true;
	app.clear(sf::Color::Black);
	std::vector<std::string> currentWords = codeDict.generateWords(25);
	// for(int i =0;i< 25;i++) {
	// 	std::cout << currentWords[i] << std::endl;
	// }
	for(int i = 0; i < 5;++i) {
		std::vector<Button> temp;
		for(int j = 0; j < 5;++j) {
			sf::Vector2f tempButtonSize(app.getSize().x/8, app.getSize().y/10);
			sf::Vector2f tempButtonLoc(100+app.getSize().x/8+(j*50)+((app.getSize().x/8)*j),
                    50+app.getSize().y/10+(40*i)+((app.getSize().y/10)*i));

			Button tempBtn(currentWords[count],tempButtonLoc,tempButtonSize, sf::Color::White,
				app.getSize().x/38,count);

			sf::Vector2f theShift(tempButtonLoc.x, 
				tempButtonLoc.y + 2*(app.getSize().y/100));
			std::cout << theShift.x << " " << theShift.y << std::endl;
			tempBtn.shiftTextInside(theShift, app);
			temp.push_back(tempBtn);
			tempBtn.draw(app);
			count++;
		}
	}

	Button QuitButton("Quit", sf::Vector2f(0, 0), sf::Vector2f(app.getSize().x/12, app.getSize().y/16),
	 sf::Color::Red, app.getSize().x/30,0);
	
	Button SpymasterButton("Spymaster Board", sf::Vector2f(app.getSize().x/3, 0), sf::Vector2f(app.getSize().x/3.5, app.getSize().y/15),
	 sf::Color::Blue, app.getSize().x/40,1);

	QuitButton.draw(app);
	SpymasterButton.draw(app);


	ButtonActions allBtnActions;
    allBtnActions.update_keybind(0, &closeItAllNow);
    //allBtnActions.update_keybind(1, &openSpyMasterBoard);

    bool l = false;
	while(running) {
		while(app.pollEvent(event)) {


			if(QuitButton.checkClick(app)) {
				allBtnActions.key_pressed(QuitButton.buttonId, app);//Do associated action with button
			}
			if(SpymasterButton.checkClick(app)) {
				//allBtnActions.key_pressed_event(SpymasterButton.buttonId, event);//Do associated action with button
				if(l == false) {
					sf::Thread thread(&spawn);
    				thread.launch();
    				l=true;
				}

			}				
			//SpymasterButton.checkClick(app, allBtnActions);

			if(event.type == sf::Event::Closed) { //If Wind Closed
				std::cout << "Closing PlayBoard Screen" << std::endl;
				return -1;
			}

			
			app.display();
		}
	}
	return 0;
}

