#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <string>

// Forward Declarations
struct GLFWwindow;

class Window
{
public:
    Window() = delete;
    Window(const std::string& title, const uint32_t height, const uint32_t width);
    virtual ~Window();

    Window(const Window& other) = delete;
    Window(Window&& other) noexcept;

    Window& operator=(const Window& other) = delete;
    Window& operator=(Window&& other) noexcept;

    // Accessors
    float aspect_ratio() const;
    int height() const;
    int width() const;

    // Input Functions
    void poll_input();

    // Callback handlers
    void handle_key_event(int key, int scancode, int action, int mods);
    void handle_cursor_position_event(double xpos, double ypos);
    void handle_mouse_button_event(int button, int action, int mods);

    // Mouse Position
    double mouse_x_position() const;
    double mouse_y_position() const;

    // Mouse buttons
    bool left_mouse_button_is_pressed() const;
    bool right_mouse_button_is_pressed() const;

    // IMGUI initializer
    void register_imgui() const;

    // GLFW Wrappers
    void swap_buffers() const;

    bool should_close() const;
    bool should_not_close() const;

    void enable_vsync() const;
    void disable_vsync() const;

    // OpenGL Wrappers
    void clear_color(const float red,
                     const float green,
                     const float blue,
                     const float alpha) const;
    void clear_buffer_bits() const;

    void enable_wireframe() const;
    void disable_wireframe() const;

    void enable_depth_test() const;
    void disable_depth_test() const;

    void enable_backface_culling() const;
    void disable_backface_culling() const;

private:
    GLFWwindow* m_window_pointer;

    bool m_left_mouse_button_is_pressed;
    bool m_right_mouse_button_is_pressed;

    double m_old_mouse_x_position;
    double m_old_mouse_y_position;

    double m_mouse_x_position;
    double m_mouse_y_position;
};

#endif
