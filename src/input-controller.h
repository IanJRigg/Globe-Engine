#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <cstdint>

class Input_Controller
{
public:
    Input_Controller();
    virtual ~Input_Controller() = default;

    Input_Controller(Input_Controller& other) = delete;
    Input_Controller(Input_Controller&& other) noexcept;

    Input_Controller& operator=(Input_Controller& other) = delete;
    Input_Controller& operator=(Input_Controller&& other) noexcept;

    void process_input();

    // System Levlel Inputs
    bool quit_was_pressed() const;

    // Mouse Position
    int32_t mouse_x_position() const;
    int32_t mouse_y_position() const;


// Key Pressed
    // Mouse buttons
    bool left_mouse_button_is_pressed() const;
    bool right_mouse_button_is_pressed() const;

    // Arrow Keys
    bool up_key_is_pressed() const;
    bool down_key_is_pressed() const;
    bool left_key_is_pressed() const;
    bool right_key_is_pressed() const;

    // Mouse Motion
    float mouse_x_input() const;
    float mouse_y_input() const;

    // Whitespace keys
    bool tab_key_is_pressed() const;
    bool return_key_is_pressed() const;
    bool space_key_is_pressed() const;
    bool backspace_key_is_pressed() const;

    // Number keys
    bool zero_key_is_pressed() const;
    bool one_key_is_pressed() const;
    bool two_key_is_pressed() const;
    bool three_key_is_pressed() const;
    bool four_key_is_pressed() const;
    bool five_key_is_pressed() const;
    bool six_key_is_pressed() const;
    bool seven_key_is_pressed() const;
    bool eight_key_is_pressed() const;
    bool nine_key_is_pressed() const;

    // Special character keys
    bool single_quote_key_is_pressed() const;
    bool comma_key_is_pressed() const;
    bool minus_key_is_pressed() const;
    bool period_key_is_pressed() const;
    bool slash_key_is_pressed() const;
    bool semicolon_key_is_pressed() const;
    bool equals_key_is_pressed() const;
    bool left_brackect_key_is_pressed() const;
    bool backslash_key_is_pressed() const;
    bool right_bracket_key_is_pressed() const;

    // Letter keys
    bool a_key_is_pressed() const;
    bool b_key_is_pressed() const;
    bool c_key_is_pressed() const;
    bool d_key_is_pressed() const;
    bool e_key_is_pressed() const;
    bool f_key_is_pressed() const;
    bool g_key_is_pressed() const;
    bool h_key_is_pressed() const;
    bool i_key_is_pressed() const;
    bool j_key_is_pressed() const;
    bool k_key_is_pressed() const;
    bool l_key_is_pressed() const;
    bool m_key_is_pressed() const;
    bool n_key_is_pressed() const;
    bool o_key_is_pressed() const;
    bool p_key_is_pressed() const;
    bool q_key_is_pressed() const;
    bool r_key_is_pressed() const;
    bool s_key_is_pressed() const;
    bool t_key_is_pressed() const;
    bool u_key_is_pressed() const;
    bool v_key_is_pressed() const;
    bool w_key_is_pressed() const;
    bool x_key_is_pressed() const;
    bool y_key_is_pressed() const;
    bool z_key_is_pressed() const;

    // Function Keys
    bool f1_key_is_pressed() const;
    bool f2_key_is_pressed() const;
    bool f3_key_is_pressed() const;
    bool f4_key_is_pressed() const;
    bool f5_key_is_pressed() const;
    bool f6_key_is_pressed() const;
    bool f7_key_is_pressed() const;
    bool f8_key_is_pressed() const;
    bool f9_key_is_pressed() const;
    bool f10_key_is_pressed() const;
    bool f11_key_is_pressed() const;
    bool f12_key_is_pressed() const;


// Key Down
    // Mouse buttons
    bool left_mouse_button_down() const;
    bool right_mouse_button_down() const;

    // Arrow Keys
    bool up_key_down() const;
    bool down_key_down() const;
    bool left_key_down() const;
    bool right_key_down() const;

    // Whitespace keys
    bool tab_key_down() const;
    bool return_key_down() const;
    bool space_key_down() const;
    bool backspace_key_down() const;

    // Number keys
    bool zero_key_down() const;
    bool one_key_down() const;
    bool two_key_down() const;
    bool three_key_down() const;
    bool four_key_down() const;
    bool five_key_down() const;
    bool six_key_down() const;
    bool seven_key_down() const;
    bool eight_key_down() const;
    bool nine_key_down() const;

    // Special character keys
    bool single_quote_key_down() const;
    bool comma_key_down() const;
    bool minus_key_down() const;
    bool period_key_down() const;
    bool slash_key_down() const;
    bool semicolon_key_down() const;
    bool equals_key_down() const;
    bool left_brackect_key_down() const;
    bool backslash_key_down() const;
    bool right_bracket_key_down() const;

    // Letter keys
    bool a_key_down() const;
    bool b_key_down() const;
    bool c_key_down() const;
    bool d_key_down() const;
    bool e_key_down() const;
    bool f_key_down() const;
    bool g_key_down() const;
    bool h_key_down() const;
    bool i_key_down() const;
    bool j_key_down() const;
    bool k_key_down() const;
    bool l_key_down() const;
    bool m_key_down() const;
    bool n_key_down() const;
    bool o_key_down() const;
    bool p_key_down() const;
    bool q_key_down() const;
    bool r_key_down() const;
    bool s_key_down() const;
    bool t_key_down() const;
    bool u_key_down() const;
    bool v_key_down() const;
    bool w_key_down() const;
    bool x_key_down() const;
    bool y_key_down() const;
    bool z_key_down() const;

    // Function Keys
    bool f1_key_down() const;
    bool f2_key_down() const;
    bool f3_key_down() const;
    bool f4_key_down() const;
    bool f5_key_down() const;
    bool f6_key_down() const;
    bool f7_key_down() const;
    bool f8_key_down() const;
    bool f9_key_down() const;
    bool f10_key_down() const;
    bool f11_key_down() const;
    bool f12_key_down() const;


// Key Up
    // Mouse buttons
    bool left_mouse_button_is_up() const;
    bool right_mouse_button_is_up() const;

    // Arrow Keys
    bool up_key_up() const;
    bool down_key_up() const;
    bool left_key_up() const;
    bool right_key_up() const;

    // Whitespace keys
    bool tab_key_up() const;
    bool return_key_up() const;
    bool space_key_up() const;
    bool backspace_key_up() const;

    // Number keys
    bool zero_key_up() const;
    bool one_key_up() const;
    bool two_key_up() const;
    bool three_key_up() const;
    bool four_key_up() const;
    bool five_key_up() const;
    bool six_key_up() const;
    bool seven_key_up() const;
    bool eight_key_up() const;
    bool nine_key_up() const;

    // Special character keys
    bool single_quote_key_up() const;
    bool comma_key_up() const;
    bool minus_key_up() const;
    bool period_key_up() const;
    bool slash_key_up() const;
    bool semicolon_key_up() const;
    bool equals_key_up() const;
    bool left_brackect_key_up() const;
    bool backslash_key_up() const;
    bool right_bracket_key_up() const;

    // Letter keys
    bool a_key_up() const;
    bool b_key_up() const;
    bool c_key_up() const;
    bool d_key_up() const;
    bool e_key_up() const;
    bool f_key_up() const;
    bool g_key_up() const;
    bool h_key_up() const;
    bool i_key_up() const;
    bool j_key_up() const;
    bool k_key_up() const;
    bool l_key_up() const;
    bool m_key_up() const;
    bool n_key_up() const;
    bool o_key_up() const;
    bool p_key_up() const;
    bool q_key_up() const;
    bool r_key_up() const;
    bool s_key_up() const;
    bool t_key_up() const;
    bool u_key_up() const;
    bool v_key_up() const;
    bool w_key_up() const;
    bool x_key_up() const;
    bool y_key_up() const;
    bool z_key_up() const;

    // Function Keys
    bool f1_key_up() const;
    bool f2_key_up() const;
    bool f3_key_up() const;
    bool f4_key_up() const;
    bool f5_key_up() const;
    bool f6_key_up() const;
    bool f7_key_up() const;
    bool f8_key_up() const;
    bool f9_key_up() const;
    bool f10_key_up() const;
    bool f11_key_up() const;
    bool f12_key_up() const;

private:
    void clear_input_map();

private:
    // Window State
    bool m_quit_button_is_pressed;

    // Mouse Button State
    bool m_left_mouse_button_is_pressed;
    bool m_right_mouse_button_is_pressed;

    int32_t m_old_mouse_x_position;
    int32_t m_old_mouse_y_position;

    int32_t m_mouse_x_position;
    int32_t m_mouse_y_position;
};

#endif