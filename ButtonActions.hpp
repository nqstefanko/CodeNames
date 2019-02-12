#ifndef BUTTON_ACTIONS
#define BUTTON_ACTIONS

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ButtonActions
{
public:
    std::vector<void(*)(sf::RenderWindow & app)> actions;

    std::vector<void(*)(sf::Event & e)> events;
    //actions.reserve(10);
    // 
    void key_pressed(int buttonId, sf::RenderWindow & app);
    void key_pressed_event(int buttonId, sf::Event & e);

    // update keybind from menu
    void update_keybind(int buttonId, void(*new_action)(sf::RenderWindow & app));
    void update_keybind_event(int buttonId, void(*new_action)(sf::Event & e));

};

#endif