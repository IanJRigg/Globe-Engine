#include <iostream>

#include <cstring>
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t Received_SIGABRT = 0L;
volatile sig_atomic_t Received_SIGFPE  = 0L;
volatile sig_atomic_t Received_SIGHUP  = 0L;
volatile sig_atomic_t Received_SIGILL  = 0L;
volatile sig_atomic_t Received_SIGINT  = 0L;
volatile sig_atomic_t Received_SIGKILL = 0L;
volatile sig_atomic_t Received_SIGPIPE = 0L;
volatile sig_atomic_t Received_SIGQUIT = 0L;
volatile sig_atomic_t Received_SIGTERM = 0L;
volatile sig_atomic_t Received_SIGUSR1 = 0L;
volatile sig_atomic_t Received_SIGUSR2 = 0L;

/**********************************************************************************************//**
 * \brief Signal handler for every catchable signal
 *  \param signal Incoming POSIX signal identifier
 *************************************************************************************************/
static void handle_signal(int signal)
{
    switch(signal)
    {
        case SIGABRT: Received_SIGABRT = signal; break;
        case SIGFPE:  Received_SIGFPE  = signal; break;
        case SIGHUP:  Received_SIGHUP  = signal; break;
        case SIGILL:  Received_SIGILL  = signal; break;
        case SIGINT:  Received_SIGINT  = signal; break;
        case SIGPIPE: Received_SIGPIPE = signal; break;
        case SIGQUIT: Received_SIGQUIT = signal; break;
        case SIGTERM: Received_SIGTERM = signal; break;
        case SIGUSR1: Received_SIGUSR1 = signal; break;
        case SIGUSR2: Received_SIGUSR2 = signal; break;

        case SIGSEGV:
        default:
            _exit(1L); // Very important, exit(1L) is not re-entrant, but _exit(1L) is
            break;
    }
}

/**********************************************************************************************//**
 * \brief Utility function to check if a recoverable signal has been caught
 *  \return true if no signals have been caught
 *  \return false if a signal has been caught
 *************************************************************************************************/
static bool no_signals_have_been_raised()
{
    if(Received_SIGABRT != 0L)
    {
        printf("Received SIGABRT\n");
        return false;
    }

    if(Received_SIGFPE  != 0L)
    {
        printf("Received SIGFPE\n");
        return false;
    }

    if(Received_SIGHUP  != 0L)
    {
        printf("Received SIGHUP\n");
        return false;
    }

    if(Received_SIGILL  != 0L)
    {
        printf("Received SIGILL\n");
        return false;
    }

    if(Received_SIGINT  != 0L)
    {
        printf("Received SIGINT\n");
        return false;
    }

    if(Received_SIGPIPE != 0L)
    {
        printf("Received SIGPIPE\n");
        return false;
    }

    if(Received_SIGQUIT != 0L)
    {
        printf("Received SIGQUIT\n");
        return false;
    }

    if(Received_SIGTERM != 0L)
    {
        printf("Received SIGTERM\n");
        return false;
    }

    if(Received_SIGUSR1 != 0L)
    {
        printf("Received SIGUSR1\n");
        return false;
    }

    if(Received_SIGUSR2 != 0L)
    {
        printf("Received SIGUSR2\n");
        return false;
    }

    return true;
}

/**********************************************************************************************//**
 * \brief Signal handler initialization function
 *************************************************************************************************/
static void setup_signal_handlers()
{
    struct sigaction sa;
    memset(&sa, 0U, sizeof(sa));

    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGABRT, &sa, NULL) == -1L)
    {
        perror("SIGABRT");
        exit(1L);
    }

    if(sigaction(SIGFPE,  &sa, NULL) == -1L)
    {
        perror("SIGFPE");
        exit(1L);
    }

    if(sigaction(SIGHUP,  &sa, NULL) == -1L)
    {
        perror("SIGHUP");
        exit(1L);
    }

    if(sigaction(SIGILL,  &sa, NULL) == -1L)
    {
        perror("SIGILL");
        exit(1L);
    }

    if(sigaction(SIGINT,  &sa, NULL) == -1L)
    {
        perror("SIGINT");
        exit(1L);
    }

    if(sigaction(SIGPIPE, &sa, NULL) == -1L)
    {
        perror("SIGPIPE");
        exit(1L);
    }

    if(sigaction(SIGQUIT, &sa, NULL) == -1L)
    {
        perror("SIGQUIT");
        exit(1L);
    }

    if(sigaction(SIGTERM, &sa, NULL) == -1L)
    {
        perror("SIGTERM");
        exit(1L);
    }

    if(sigaction(SIGUSR1, &sa, NULL) == -1L)
    {
        perror("SIGUSR1");
        exit(1L);
    }

    if(sigaction(SIGUSR2, &sa, NULL) == -1L)
    {
        perror("SIGUSR2");
        exit(1L);
    }

    if(sigaction(SIGSEGV, &sa, NULL) == -1L)
    {
        perror("SIGSEGV");
        exit(1L);
    }
}

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.h"
#include "texture.h"
#include "buffer-controller.h"
#include "input-controller.h"
#include "window.h"

int32_t mix = 0;

const std::vector<float> cube_vertices {
//    Positions               Colors                 Texture coords
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f
};

void chapter_7()
{
    Window window("LearnOpenGL Chapter 7", 768UL, 1024UL);
    window.enable_vsync();
    window.enable_depth_test();
    window.enable_backface_culling();

    Input_Controller input_controller;
    window.register_input_controller(input_controller);

    std::vector<float> vertices {
    //    Positions               Colors                 Texture coords
           0.5f,  0.5f,  0.0f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f, // Top Right
           0.5f, -0.5f,  0.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f, // Bottom right
          -0.5f, -0.5f,  0.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f, // Bottom left
          -0.5f,  0.5f,  0.0f,    1.0f,  1.0f,  0.0f,    0.0f, 1.0f  // top left
    };

    std::vector<uint32_t> indices{
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Buffer_Controller buffer_controller;
    buffer_controller.load_array_buffer(vertices);
    buffer_controller.load_element_array_buffer(indices);
    buffer_controller.set_array_attribute(0, 3, 0);
    buffer_controller.set_array_attribute(1, 3, 3);
    buffer_controller.set_array_attribute(2, 2, 6);

    Texture_2D texture_1;
    texture_1.bind();
    texture_1.load_jpg("textures/container.jpg");
    texture_1.set_s_axis_to_repeat();
    texture_1.set_t_axis_to_repeat();
    texture_1.set_minifying_filter_to_nearest();
    texture_1.set_magnifying_filter_to_nearest();

    Texture_2D texture_2;
    texture_2.bind();
    texture_2.load_png("textures/awesomeface.png");
    texture_2.set_s_axis_to_repeat();
    texture_2.set_t_axis_to_repeat();
    texture_2.set_minifying_filter_to_nearest();
    texture_2.set_magnifying_filter_to_nearest();

    Program program;
    program.load_vertex_shader("shaders/vertex/ex-7.vert");
    program.load_fragment_shader("shaders/fragment/ex-7.frag");
    program.link();

    program.use();

    program.set_uniform_integer("texture1", 0);
    program.set_uniform_integer("texture2", 1);

    while(no_signals_have_been_raised())
    {
        if(window.should_close())
        {
            break;
        }

        if(input_controller.up_key_is_pressed())
        {
            if(mix < 10L)
            {
                 mix++;
            }
        }
        else if(input_controller.down_key_is_pressed())
        {
            if(mix > 0L)
            {
                mix--;
            }
        }

        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        texture_1.set_active_texture(GL_TEXTURE0);
        texture_1.bind();

        texture_2.set_active_texture(GL_TEXTURE1);
        texture_2.bind();

        program.use();

        program.set_uniform_float("mixValue", mix);

        buffer_controller.bind();
        buffer_controller.draw();

        window.swap_buffers();
    }
}

void chapter_8()
{
    Window window("LearnOpenGL Chapter 8", 768UL, 1024UL);
    window.enable_vsync();
    window.enable_depth_test();
    window.enable_backface_culling();

    Input_Controller input_controller;
    window.register_input_controller(input_controller);

    std::vector<float> vertices {
    //    Positions               Colors                 Texture coords
           0.5f,  0.5f,  0.0f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f, // Top Right
           0.5f, -0.5f,  0.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f, // Bottom right
          -0.5f, -0.5f,  0.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f, // Bottom left
          -0.5f,  0.5f,  0.0f,    1.0f,  1.0f,  0.0f,    0.0f, 1.0f  // top left
    };

    std::vector<uint32_t> indices {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Buffer_Controller buffer_controller;
    buffer_controller.bind();
    buffer_controller.load_array_buffer(vertices);
    buffer_controller.load_element_array_buffer(indices);
    buffer_controller.set_array_attribute(0, 3, 0);
    buffer_controller.set_array_attribute(1, 3, 3);
    buffer_controller.set_array_attribute(2, 2, 6);

    Texture_2D texture_1;
    texture_1.bind();
    texture_1.load_jpg("textures/container.jpg");
    texture_1.set_s_axis_to_repeat();
    texture_1.set_t_axis_to_repeat();
    texture_1.set_minifying_filter_to_nearest();
    texture_1.set_magnifying_filter_to_nearest();

    Texture_2D texture_2;
    texture_2.bind();
    texture_2.load_png("textures/awesomeface.png");
    texture_2.set_s_axis_to_repeat();
    texture_2.set_t_axis_to_repeat();
    texture_2.set_minifying_filter_to_nearest();
    texture_2.set_magnifying_filter_to_nearest();

    Program program;
    program.load_vertex_shader("shaders/vertex/ex-7.vert");
    program.load_fragment_shader("shaders/fragment/ex-7.frag");
    program.link();

    program.use();
    program.set_uniform_integer("texture1", 0);
    program.set_uniform_integer("texture2", 1);

    while(no_signals_have_been_raised())
    {
        if(window.should_close())
        {
            break;
        }

        if(input_controller.up_key_is_pressed())
        {
            if(mix < 10L)
            {
                 mix++;
            }
        }
        else if(input_controller.down_key_is_pressed())
        {
            if(mix > 0L)
            {
                mix--;
            }
        }

        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        texture_1.set_active_texture(GL_TEXTURE0);
        texture_1.bind();

        texture_2.set_active_texture(GL_TEXTURE1);
        texture_2.bind();

        program.use();
        program.set_uniform_float("mixValue", mix / 10.0f);

        buffer_controller.bind();
        buffer_controller.draw();

        window.swap_buffers();
    }
}

void chapter_9()
{
    Window window("LearnOpenGL Chapter 9", 768UL, 1024UL);
    window.enable_vsync();
    window.enable_depth_test();
    window.enable_backface_culling();

    Input_Controller input_controller;
    window.register_input_controller(input_controller);

    // Buffer_Controller buffer_controller;
    // buffer_controller.bind();
    // buffer_controller.load_array_buffer(cube_vertices);
    // buffer_controller.set_array_attribute(0, 3, 0);
    // buffer_controller.set_array_attribute(1, 3, 3);
    // buffer_controller.set_array_attribute(2, 2, 6);

    // Texture_2D texture;
    // texture.bind();
    // texture.load_jpg("textures/container.jpg");
    // texture.set_s_axis_to_repeat();
    // texture.set_t_axis_to_repeat();
    // texture.set_minifying_filter_to_nearest();
    // texture.set_magnifying_filter_to_nearest();

    // Program program;
    // program.load_vertex_shader("shaders/vertex/ex-9.vert");
    // program.load_fragment_shader("shaders/fragment/ex-9.frag");
    // program.link();

    // program.use();

    // program.set_uniform_integer("texture1", 0);

    // Input_Controller input_controller;

    // glm::mat4 transformation(1.0f);

    // glm::vec3 x_axis(1.0f, 0.0f, 0.0f);
    // glm::vec3 y_axis(0.0f, 1.0f, 0.0f);
    // glm::vec3 rotation_axis(0.0f, 0.0f, 0.0f);
    // glm::mat4 rotation(1.0f);

    // glm::mat4 scale(1.0f);
    // glm::mat4 model(1.0f);

    // glm::mat4 view = glm::lookAt(
    //     glm::vec3(0.0f, 0.0f, 2.0f),
    //     glm::vec3(0.0f, 0.0f, 0.0f),
    //     glm::vec3(0.0f, 1.0f, 0.0f)
    // );

    // float fov = 45.0f;
    // glm::mat4 projection = glm::perspective(glm::radians(fov), (4.0f/3.0f), 0.1f, 100.0f);

    // glm::mat4 mvp(1.0f);

    // float rotation_angle = 0.0f;

    // bool left_click_is_being_held_down = false;

    while(no_signals_have_been_raised())
    {
        if(window.should_close())
        {
            break;
        }

        window.poll_input();

        // if(input_controller.left_mouse_button_is_pressed())
        // {
        //     if(left_click_is_being_held_down)
        //     {
        //         std::cout << "Holding" << std::endl;
        //         //rotation_axis.x = input_controller.mouse_x_input();
        //         //rotation_axis.y = input_controller.mouse_y_input();
        //         if(/*input_controller.mouse_x_input() ||*/ input_controller.mouse_y_input())
        //         {
        //             rotation_angle += input_controller.mouse_y_input();
        //             if(rotation_angle >= 360.0f || rotation_angle <= -360.0f)
        //             {
        //                 rotation_angle = 0.0f;
        //             }

        //             rotation = glm::rotate(rotation, glm::radians(rotation_angle), x_axis);
        //         }
        //     }
        //     else
        //     {
        //         std::cout << "First click" << std::endl;
        //         left_click_is_being_held_down = true;
        //     }
        // }
        // else
        // {
        //     left_click_is_being_held_down = false;
        // }

        // if(input_controller.up_key_is_pressed())
        // {
        //     rotation = glm::rotate(rotation, glm::radians(5.0f), x_axis);
        // }

        // if(input_controller.down_key_is_pressed())
        // {
        //     rotation = glm::rotate(rotation, glm::radians(-5.0f), x_axis);
        // }

        // if(input_controller.right_key_is_pressed())
        // {
        //     rotation = glm::rotate(rotation, glm::radians(-5.0f), y_axis);
        // }

        // if(input_controller.left_key_is_pressed())
        // {
        //     rotation = glm::rotate(rotation, glm::radians(5.0f), y_axis);
        // }

        // Start rendering
        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        // texture.set_active_texture(GL_TEXTURE0);
        // texture.bind();

        // program.use();

        // projection = glm::perspective(glm::radians(fov), (4.0f/3.0f), 0.1f, 100.0f);

        // model = transformation * rotation * scale;
        // mvp = projection * view * model;

        // program.set_uniform_mat4("mvp", mvp);

        // buffer_controller.bind();
        // buffer_controller.draw();

        window.swap_buffers();
    }
}

void chapter_10()
{
    Window window("LearnOpenGL Chapter 10", 768UL, 1024UL);
    window.enable_vsync();
    window.enable_depth_test();
    window.enable_backface_culling();

    Input_Controller input_controller;
    window.register_input_controller(input_controller);

    // View Space Transformation Matrices
    glm::mat4 transformation(1.0f);

    glm::vec3 rotation_axis(0.0f, 1.0f, 0.0f);
    glm::mat4 rotation(1.0f);

    glm::mat4 scale(1.0f);
    glm::mat4 model(1.0f);

    // Camera
    glm::vec3 cameraPos   = glm::vec3(0.0f,  0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f,  0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f,  1.0f,  0.0f);

    glm::mat4 view = glm::lookAt(
        cameraPos,
        cameraPos + cameraFront,
        cameraUp
    );

    // Object initialization
    Buffer_Controller buffer_controller;
    buffer_controller.bind();
    buffer_controller.load_array_buffer(cube_vertices);
    buffer_controller.set_array_attribute(0, 3, 0);
    buffer_controller.set_array_attribute(1, 3, 3);
    buffer_controller.set_array_attribute(2, 2, 6);

    Texture_2D texture;
    texture.bind();
    texture.load_jpg("textures/container.jpg");
    texture.set_s_axis_to_repeat();
    texture.set_t_axis_to_repeat();
    texture.set_minifying_filter_to_nearest();
    texture.set_magnifying_filter_to_nearest();

    Program program;
    program.load_vertex_shader("shaders/vertex/ex-9.vert");
    program.load_fragment_shader("shaders/fragment/ex-9.frag");
    program.link();

    program.use();

    program.set_uniform_integer("texture1", 0);

    // Matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (4.0f/3.0f), 0.1f, 100.0f);
    glm::mat4 mvp(1.0f);

    while(no_signals_have_been_raised())
    {
        // Check for input
        if(input_controller.up_key_is_pressed())
        {

        }

        if(input_controller.down_key_is_pressed())
        {

        }

        if(input_controller.right_key_is_pressed())
        {
            rotation = glm::rotate(rotation, glm::radians(-10.0f), rotation_axis);
        }

        if(input_controller.left_key_is_pressed())
        {
            rotation = glm::rotate(rotation, glm::radians(10.0f), rotation_axis);
        }

        // Update Matrices
        view = glm::lookAt(
            cameraPos,
            cameraPos + cameraFront,
            cameraUp
        );

        // Start rendering
        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        texture.set_active_texture(GL_TEXTURE0);
        texture.bind();

        program.use();

        projection = glm::perspective(glm::radians(45.0f), (4.0f/3.0f), 0.1f, 100.0f);

        model = transformation * rotation * scale;
        mvp = projection * view * model;

        program.set_uniform_mat4("mvp", mvp);

        buffer_controller.bind();
        buffer_controller.draw();

        window.swap_buffers();
    }
}

/**********************************************************************************************//**
 * \brief Signal handler initialization function
 * \param argc The number of arguments
 * \param argv The argument vector
 *************************************************************************************************/
int main()
{
    setup_signal_handlers();

    chapter_9();

    return EXIT_SUCCESS;
}
