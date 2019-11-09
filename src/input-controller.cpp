#include "input-controller.h"

#include <exception>

/**********************************************************************************************//**
 * \brief Defult constructor
 *************************************************************************************************/
Input_Controller::Input_Controller() :
    m_quit_button_is_pressed(false),
    m_left_mouse_button_is_pressed(false),
    m_right_mouse_button_is_pressed(false),
    m_old_mouse_x_position(0L),
    m_old_mouse_y_position(0L),
    m_mouse_x_position(0L),
    m_mouse_y_position(0L)
{

}

/**********************************************************************************************//**
 * \brief Move constructor
 *************************************************************************************************/
Input_Controller::Input_Controller(Input_Controller&& other) noexcept
{
    *this = std::move(other);
}

/**********************************************************************************************//**
 * \brief Move assignment constructor
 *************************************************************************************************/
Input_Controller& Input_Controller::operator=(Input_Controller&& other) noexcept
{
    if(this != &other)
    {
        std::swap(m_quit_button_is_pressed, other.m_quit_button_is_pressed);
        std::swap(m_left_mouse_button_is_pressed, other.m_left_mouse_button_is_pressed);
        std::swap(m_right_mouse_button_is_pressed, other.m_right_mouse_button_is_pressed);
        std::swap(m_old_mouse_x_position, other.m_old_mouse_x_position);
        std::swap(m_old_mouse_y_position, other.m_old_mouse_y_position);
        std::swap(m_mouse_x_position, other.m_mouse_x_position);
        std::swap(m_mouse_y_position, other.m_mouse_y_position);
    }

    return *this;
}
#include <iostream>
/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Input_Controller::process_input()
{
    // SDL_Event event = { 0 };
    // bool mouse_has_not_moved = true;

    // while(SDL_PollEvent(&event))
    // {
    //     // Esc button is pressed
    //     if(event.type == SDL_QUIT)
    //     {
    //         m_quit_button_is_pressed = true;
    //     }
    //     else if(event.type == SDL_MOUSEBUTTONDOWN)
    //     {
    //         switch(event.button.button)
    //         {
    //             case SDL_BUTTON_LEFT:  m_left_mouse_button_is_pressed  = true; std::cout << "FUCK" << std::endl; break;
    //             case SDL_BUTTON_RIGHT: m_right_mouse_button_is_pressed = true;  break;
    //             default: break;
    //         }
    //     }
    //     else if(event.type == SDL_MOUSEBUTTONUP)
    //     {
    //         switch(event.button.button)
    //         {
    //             case SDL_BUTTON_LEFT:  m_left_mouse_button_is_pressed  = false; std::cout << "SHITBALLS" << std::endl; break;
    //             case SDL_BUTTON_RIGHT: m_right_mouse_button_is_pressed = false;  break;
    //             default: break;
    //         }
    //     }
    //     else if(event.type == SDL_MOUSEMOTION)
    //     {
    //         m_old_mouse_x_position = m_mouse_x_position;
    //         m_old_mouse_y_position = m_mouse_y_position;

    //         m_mouse_x_position = event.motion.x;
    //         m_mouse_y_position = event.motion.y;

    //         mouse_has_not_moved = false;
    //     }
    //     else
    //     {
    //         std::cout << event.type << std::endl;
    //     }
    // }

    // // Since SDL won't report the mouse staying in the same place, we need to record this info
    // if(mouse_has_not_moved)
    // {
    //     m_old_mouse_x_position = m_mouse_x_position;
    //     m_old_mouse_y_position = m_mouse_y_position;
    // }
}

/**********************************************************************************************//**
 * \brief  Checks if the quit button is pressed
 * \return true if quit button is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::quit_was_pressed() const
{
    return m_quit_button_is_pressed;
}

/**********************************************************************************************//**
 * \brief  Accessor for the mouse's x position
 * \return The value in m_mouse_position_x
 *************************************************************************************************/
int32_t Input_Controller::mouse_x_position() const
{
    return m_mouse_x_position;
}

/**********************************************************************************************//**
 * \brief  Accessor for the mouse's y position
 * \return The value in m_mouse_position_y
 *************************************************************************************************/
int32_t Input_Controller::mouse_y_position() const
{
    return m_mouse_y_position;
}

/**********************************************************************************************//**
 * \brief  Checks if the left mouse button is pressed
 * \return true if the left mouse button is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::left_mouse_button_is_pressed() const
{
    return m_left_mouse_button_is_pressed;
}

/**********************************************************************************************//**
 * \brief  Checks if the right mouse button is pressed
 * \return true if the right mouse button is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::right_mouse_button_is_pressed() const
{
    return m_right_mouse_button_is_pressed;
}

/**********************************************************************************************//**
 * \brief  Checks if the up key is pressed
 * \return true if up is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::up_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the down key is pressed
 * \return true if down is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::down_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the left key is pressed
 * \return true if left is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::left_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the right key is pressed
 * \return true if right is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::right_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the mouse has move in the x direction
 * \return -1 if mouse has moved left, 1 if mouse has moved right, and 0 if it hasn't changed
 *************************************************************************************************/
float Input_Controller::mouse_x_input() const
{
    int32_t difference = m_mouse_x_position - m_old_mouse_x_position;
    if(difference >= 1L)
    {
        return 0.1f;
    }
    else if(difference <= -1L)
    {
        return -0.1f;
    }
    else
    {
        return 0.0f;
    }
}

/**********************************************************************************************//**
 * \brief  Checks if the mouse has move in the y direction
 * \return -1 if mouse has moved down, 1 if mouse has moved up, and 0 if it hasn't changed
 *************************************************************************************************/
float Input_Controller::mouse_y_input() const
{
    int32_t difference = m_mouse_y_position - m_old_mouse_y_position;
    if(difference >= 1L)
    {
        return 0.1f;
    }
    else if(difference <= -1L)
    {
        return -0.1f;
    }
    else
    {
        return 0.0f;
    }
}

/**********************************************************************************************//**
 * \brief  Checks if the tab key is pressed
 * \return true if tab is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::tab_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the return key is pressed
 * \return true if return is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::return_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the space key is pressed
 * \return true if space is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::space_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the backspace key is pressed
 * \return true if backspace is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::backspace_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 0 key is pressed
 * \return true if 0 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::zero_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 1 key is pressed
 * \return true if 1 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::one_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 2 key is pressed
 * \return true if 2 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::two_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 3 key is pressed
 * \return true if 3 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::three_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 4 key is pressed
 * \return true if 4 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::four_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 5 key is pressed
 * \return true if 5 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::five_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 6 key is pressed
 * \return true if 6 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::six_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 7 key is pressed
 * \return true if 7 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::seven_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 8 key is pressed
 * \return true if 8 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::eight_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the 9 key is pressed
 * \return true if 9 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::nine_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the ' key is pressed
 * \return true if ' is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::single_quote_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the , key is pressed
 * \return true if , is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::comma_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the - key is pressed
 * \return true if - is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::minus_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the . key is pressed
 * \return true if . is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::period_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the / key is pressed
 * \return true if / is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::slash_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the ; key is pressed
 * \return true if ; is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::semicolon_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the = key is pressed
 * \return true if = is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::equals_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the [ key is pressed
 * \return true if ] is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::left_brackect_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the \ key is pressed
 * \return true if \ is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::backslash_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the ] key is pressed
 * \return true if ] is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::right_bracket_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the a key is pressed
 * \return true if a is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::a_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the b key is pressed
 * \return true if b is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::b_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the c key is pressed
 * \return true if c is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::c_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the d key is pressed
 * \return true if d is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::d_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the e key is pressed
 * \return true if e is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::e_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the f key is pressed
 * \return true if f is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the g key is pressed
 * \return true if g is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::g_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the h key is pressed
 * \return true if h is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::h_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the i key is pressed
 * \return true if i is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::i_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the j key is pressed
 * \return true if j is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::j_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the k key is pressed
 * \return true if k is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::k_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the l key is pressed
 * \return true if l is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::l_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the m key is pressed
 * \return true if m is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::m_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the n key is pressed
 * \return true if n is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::n_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the o key is pressed
 * \return true if o is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::o_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the p key is pressed
 * \return true if p is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::p_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the q key is pressed
 * \return true if q is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::q_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the r key is pressed
 * \return true if r is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::r_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the s key is pressed
 * \return true if s is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::s_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the t key is pressed
 * \return true if t is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::t_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the u key is pressed
 * \return true if u is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::u_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the v key is pressed
 * \return true if v is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::v_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the w key is pressed
 * \return true if w is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::w_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the x key is pressed
 * \return true if x is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::x_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the y key is pressed
 * \return true if y is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::y_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the z key is pressed
 * \return true if z is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::z_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F1 key is pressed
 * \return true if F1 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f1_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F2 key is pressed
 * \return true if F2 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f2_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F3 key is pressed
 * \return true if F3 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f3_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F4 key is pressed
 * \return true if F4 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f4_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F5 key is pressed
 * \return true if F5 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f5_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F6 key is pressed
 * \return true if F6 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f6_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F7 key is pressed
 * \return true if F7 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f7_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F8 key is pressed
 * \return true if F8 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f8_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F9 key is pressed
 * \return true if F9 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f9_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F10 key is pressed
 * \return true if F10 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f10_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F11 key is pressed
 * \return true if F11 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f11_key_is_pressed() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the F11 key is pressed
 * \return true if F11 is pressed, otherwise false
 *************************************************************************************************/
bool Input_Controller::f12_key_is_pressed() const
{
    return false;
}




/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::left_mouse_button_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::right_mouse_button_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::up_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::down_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::left_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::right_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::tab_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::return_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::space_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::backspace_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::zero_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::one_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::two_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::three_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::four_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::five_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::six_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::seven_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::eight_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::nine_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::single_quote_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::comma_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::minus_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::period_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::slash_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::semicolon_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::equals_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::left_brackect_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::backslash_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::right_bracket_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::a_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::b_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::c_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::d_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::e_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::g_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::h_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::i_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::j_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::k_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::l_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::m_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::n_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::o_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::p_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::q_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::r_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::s_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::t_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::u_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::v_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::w_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::x_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::y_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::z_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f1_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f2_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f3_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f4_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f5_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f6_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f7_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f8_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f9_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f10_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f11_key_down() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key was pressed since the last frame
 * \return true if  was pressed since the last frame, otherwise false
 *************************************************************************************************/
bool Input_Controller::f12_key_down() const
{
    return false;
}



/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::left_mouse_button_is_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::right_mouse_button_is_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::up_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::down_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::left_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::right_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::tab_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::return_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::space_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::backspace_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::zero_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::one_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::two_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::three_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::four_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::five_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::six_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::seven_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::eight_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::nine_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::single_quote_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::comma_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::minus_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::period_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::slash_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::semicolon_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::equals_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::left_brackect_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::backslash_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::right_bracket_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::a_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::b_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::c_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::d_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::e_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::g_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::h_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::i_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::j_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::k_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::l_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::m_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::n_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::o_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::p_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::q_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::r_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::s_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::t_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::u_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::v_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::w_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::x_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::y_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::z_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f1_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f2_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f3_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f4_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f5_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f6_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f7_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f8_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f9_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f10_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f11_key_up() const
{
    return false;
}

/**********************************************************************************************//**
 * \brief  Checks if the  key has been released since the last frame
 * \return true if  has been released since the last frame, otherwise false
*************************************************************************************************/
bool Input_Controller::f12_key_up() const
{
    return false;
}


