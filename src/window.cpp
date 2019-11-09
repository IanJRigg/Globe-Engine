#include "window.h"

#include <exception>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

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
static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods)
{

}

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param codepoint
 *************************************************************************************************/
static void character_callback(GLFWwindow*, unsigned int codepoint)
{

}

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param xpos
 * \param ypos
 *************************************************************************************************/
static void cursor_position_callback(GLFWwindow*, doubnle xpos, double ypos)
{

}

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param button
 * \param action
 * \param mods
 *************************************************************************************************/
static void mouse_button_callback(GLFWwindow*, int button, int action, int mods)
{

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
    m_window_pointer(nullptr)
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

    // Window callbacks
    glfwSetFramebufferSizeCallback(m_window_pointer, framebuffer_size_callback);

    // Input callbacks
    glfwSetKeyCallback(m_window_pointer, key_callback);
    glfwSetCharCallback(m_window_pointer, character_callback);
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
void Window::enable_depth_test() const
{
    glEnable(GL_DEPTH_TEST);
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
