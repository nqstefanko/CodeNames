#include "ButtonActions.hpp"

void ButtonActions::key_pressed(int buttonId,sf::RenderWindow &app)
{
    if(actions[buttonId]) actions[buttonId](app);
} //Do the associated action.

// update keybind from menu
void ButtonActions::update_keybind(int buttonId, void(*new_action)(sf::RenderWindow &app))
{
    actions.push_back(new_action);
}

void ButtonActions::key_pressed_event(int buttonId,sf::Event &e)
{
    if(events[buttonId]) events[buttonId](e);
} //Do the associated action.

// update keybind from menu
void ButtonActions::update_keybind_event(int buttonId, void(*new_action)(sf::Event &e))
{
    events.push_back(new_action);
}
