#ifndef BUTTON_ACTIONS
#define BUTTON_ACTIONS
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class ButtonActions
{
public:
    std::vector<void(*)(sf::RenderWindow &app)> actions;
    //actions.reserve(10);
    // 
    void key_pressed(int buttonId,sf::RenderWindow &app);
    // update keybind from menu
    void update_keybind(int buttonId, void(*new_action)(sf::RenderWindow &app));
};

#endif