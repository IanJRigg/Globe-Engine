#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <string>

// Forward Declarations
struct GLFWwindow;
class Input_Controller;

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

    void poll_input();
    void register_input_controller(Input_Controller& input_controller);

    void swap_buffers() const;
    void clear_color(const float red,
                     const float green,
                     const float blue,
                     const float alpha) const;
    void clear_buffer_bits() const;

    bool should_close() const;

    void enable_vsync() const;
    void disable_vsync() const;

    void enable_depth_test() const;
    void disable_depth_test() const;

    void enable_backface_culling() const;
    void disable_backfase_culling() const;

private:
    GLFWwindow* m_window_pointer;
};

#endif
