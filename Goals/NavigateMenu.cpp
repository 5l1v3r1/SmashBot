#include "NavigateMenu.h"

NavigateMenu::NavigateMenu(GameState *state) : Goal(state)
{
    m_controller = Controller::Instance();
    //There is no lower strategy for menuing
    m_strategy = NULL;
    m_emptiedInput = false;
}

NavigateMenu::~NavigateMenu()
{
}

void NavigateMenu::Strategize()
{
    //Spend one frame at the start of the menu just to clear the input from anything left over
    if(!m_emptiedInput)
    {
        m_controller->emptyInput();
        m_emptiedInput = true;
        return;
    }

    if(m_state->menu_state == POSTGAME_SCORES)
    {
        if(m_state->frame % 2)
        {
            m_controller->pressButton(Controller::BUTTON_START);
        }
        else
        {
            m_controller->releaseButton(Controller::BUTTON_START);
        }
        return;
    }

    //If we're not fox, and the cursor isn't in Y position, move into position
    if((m_state->player_two_character != CHARACTER::FOX) &&
    ((m_state->player_two_pointer_y < 8) ||
    (m_state->player_two_pointer_y > 15)))
    {
        //center of fox = -23.5, 11.5
        if(m_state->player_two_pointer_y < 8)
        {
            m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 1);
        }
        else
        {
            m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
        }
        return;
    }

    //If we're not fox, and the cursor isn't in X position, move into position
    if((m_state->player_two_character != CHARACTER::FOX) &&
    ((m_state->player_two_pointer_x < -27) ||
    (m_state->player_two_pointer_x > -20)))
    {
        //center of fox = -23.5, 11.5
        if(m_state->player_two_pointer_x < -27)
        {
            m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, .5);
        }
        else
        {
            m_controller->tiltAnalog(Controller::BUTTON_MAIN, 0, .5);
        }
        return;
    }

    //If we're not fox, and the cursor _IS_ in position, select fox
    if((m_state->player_two_character != CHARACTER::FOX) &&
    ((m_state->player_two_pointer_x > -27) &&
    (m_state->player_two_pointer_x < -20) &&
    (m_state->player_two_pointer_y > 8) &&
    (m_state->player_two_pointer_y < 15)))
    {
        m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
        m_controller->pressButton(Controller::BUTTON_A);
        return;
    }
}
