#include "window.h"

#include <exception>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param width
 * \param height
 *************************************************************************************************/
static void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param key
 * \param scancode
 * \param action
 * \param mods
 *************************************************************************************************/
static void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    if(window == nullptr)
    {
        std::terminate();
    }

    window->handle_key_event(key, scancode, action, mods);
}

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param xpos
 * \param ypos
 *************************************************************************************************/
static void cursor_position_callback(GLFWwindow* glfw_window, double xpos, double ypos)
{
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    if(window == nullptr)
    {
        std::terminate();
    }

    window->handle_cursor_position_event(xpos, ypos);
}

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param button
 * \param action
 * \param mods
 *************************************************************************************************/
static void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
{
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    if(window == nullptr)
    {
        std::terminate();
    }

    window->handle_mouse_button_event(button, action, mods);
}

/**********************************************************************************************//**
 * \brief
 * \param id
 * \param description
 *************************************************************************************************/
static void error_callback(int, const char* description)
{
    std::cout << description << std::endl;
}

/**********************************************************************************************//**
 * \brief
 * \param title
 * \param width
 * \param height
 *************************************************************************************************/
Window::Window(const std::string& title, const uint32_t height, const uint32_t width) :
    m_window_pointer(nullptr),
    m_left_mouse_button_is_pressed(false),
    m_right_mouse_button_is_pressed(false),
    m_old_mouse_x_position(0.0f),
    m_old_mouse_y_position(0.0f),
    m_mouse_x_position(0.0f),
    m_mouse_y_position(0.0f)
{
    if(glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Failed to create window. Exiting..." << std::endl;
        std::terminate();
    }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    #endif

    #ifdef __linux__
        // for use later
    #endif

    #ifdef _WIN32
        // for use later
    #endif

    m_window_pointer = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(m_window_pointer == nullptr)
    {
        std::cerr << "Failed to create window" << std::endl;
        std::terminate();
    }

    glfwMakeContextCurrent(m_window_pointer);

    if(!gladLoadGL()) {
        std::cerr << "Unable to load OpenGL Extensions" << std::endl;
        std::terminate();
    }

    glfwSetWindowUserPointer(m_window_pointer, reinterpret_cast<void*>(this));

    // Window callbacks
    glfwSetFramebufferSizeCallback(m_window_pointer, framebuffer_size_callback);

    // Input callbacks
    glfwSetKeyCallback(m_window_pointer, key_callback);
    glfwSetCursorPosCallback(m_window_pointer, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window_pointer, mouse_button_callback);

    // Debug callbacks
    glfwSetErrorCallback(&error_callback);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
Window::~Window()
{
    glfwDestroyWindow(m_window_pointer);
    glfwTerminate();
}

/**********************************************************************************************//**
 * \brief
 * \param other
 *************************************************************************************************/
Window::Window(Window&& other) noexcept :
    m_window_pointer(nullptr)
{
    *this = std::move(other);
}

/**********************************************************************************************//**
 * \brief
 * \param other
 *************************************************************************************************/
Window& Window::operator=(Window&& other) noexcept
{
    if(this != &other)
    {
        std::swap(m_window_pointer, other.m_window_pointer);
        std::swap(m_left_mouse_button_is_pressed, other.m_left_mouse_button_is_pressed);
        std::swap(m_right_mouse_button_is_pressed, other.m_right_mouse_button_is_pressed);
        std::swap(m_old_mouse_x_position, other.m_old_mouse_x_position);
        std::swap(m_old_mouse_y_position, other.m_old_mouse_y_position);
        std::swap(m_mouse_x_position, other.m_mouse_x_position);
        std::swap(m_mouse_y_position, other.m_mouse_y_position);
    }

    return *this;
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::poll_input()
{
    glfwPollEvents();
}

/**********************************************************************************************//**
 * \brief Move assignment constructor
 *************************************************************************************************/
void Window::handle_key_event(int key, int scancode, int action, int)
{

}

/**********************************************************************************************//**
 * \brief Move assignment constructor
 *************************************************************************************************/
void Window::handle_cursor_position_event(double xpos, double ypos)
{
    m_old_mouse_x_position = m_mouse_x_position;
    m_old_mouse_y_position = m_mouse_y_position;

    m_mouse_x_position = xpos;
    m_mouse_y_position = ypos;
}

/**********************************************************************************************//**
 * \brief Move assignment constructor
 *************************************************************************************************/
void Window::handle_mouse_button_event(int button, int action, int)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        m_left_mouse_button_is_pressed = true;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        m_left_mouse_button_is_pressed = false;
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        m_right_mouse_button_is_pressed = true;
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        m_right_mouse_button_is_pressed = true;
    }
    else
    {
        std::cerr << "Bad input to the mouse button callback" << std::endl;
    }
}

/**********************************************************************************************//**
 * \brief  Accessor for the mouse's x position
 * \return The value in m_mouse_position_x
 *************************************************************************************************/
double Window::mouse_x_position() const
{
    return m_mouse_x_position;
}

/**********************************************************************************************//**
 * \brief  Accessor for the mouse's y position
 * \return The value in m_mouse_position_y
 *************************************************************************************************/
double Window::mouse_y_position() const
{
    return m_mouse_y_position;
}

/**********************************************************************************************//**
 * \brief  Checks if the left mouse button is pressed
 * \return true if the left mouse button is pressed, otherwise false
 *************************************************************************************************/
bool Window::left_mouse_button_is_pressed() const
{
    return m_left_mouse_button_is_pressed;
}

/**********************************************************************************************//**
 * \brief  Checks if the right mouse button is pressed
 * \return true if the right mouse button is pressed, otherwise false
 *************************************************************************************************/
bool Window::right_mouse_button_is_pressed() const
{
    return m_right_mouse_button_is_pressed;
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::register_imgui() const
{
    ImGui_ImplGlfw_InitForOpenGL(m_window_pointer, true);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::swap_buffers() const
{
    glfwSwapBuffers(m_window_pointer);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
bool Window::should_close() const
{
    return (glfwWindowShouldClose(m_window_pointer) == 1);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
bool Window::should_not_close() const
{
    return !(this->should_close());
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::enable_vsync() const
{
    glfwSwapInterval(1);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::disable_vsync() const
{
    glfwSwapInterval(0);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::clear_color(const float red,
                         const float green,
                         const float blue,
                         const float alpha) const
{
    glClearColor(red, green, blue, alpha);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::clear_buffer_bits() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::enable_depth_test() const
{
    glEnable(GL_DEPTH_TEST);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::enable_wireframe() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::disable_wireframe() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::disable_depth_test() const
{
    glDisable(GL_DEPTH_TEST);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::enable_backface_culling() const
{
    glEnable(GL_CULL_FACE);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Window::disable_backfase_culling() const
{
    glDisable(GL_CULL_FACE);
}
