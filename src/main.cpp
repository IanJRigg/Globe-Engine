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
#include "window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int32_t mix = 0;

const std::vector<float> cube_vertices {
//    Positions               Colors                 Texture coords
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,

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
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f, 0.0f
};

int main(int argc, char** argv)
{
    setup_signal_handlers();

    Window window("LearnOpenGL Chapter 9", 768UL, 1024UL);
    window.enable_vsync();
    window.enable_depth_test();
    window.enable_backface_culling();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    window.register_imgui();
    ImGui_ImplOpenGL3_Init("#version 410 core");

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

    glm::mat4 transformation(1.0f);

    glm::vec3 x_axis(1.0f, 0.0f, 0.0f);
    glm::vec3 y_axis(0.0f, 1.0f, 0.0f);
    glm::vec3 rotation_axis(0.0f, 0.0f, 0.0f);
    glm::mat4 rotation(1.0f);

    glm::mat4 scale(1.0f);
    glm::mat4 model(1.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (4.0f/3.0f), 0.1f, 100.0f);

    glm::mat4 mvp(1.0f);

    bool mouse_is_being_held_down = false;

    double start_x_position = 0.0f;
    double current_x_position = 0.0f;

    double start_y_position = 0.0f;
    double current_y_position = 0.0f;

    glm::vec3 cube_angles(0.0f, 0.0f, 0.0f);

    while(no_signals_have_been_raised() && window.should_not_close())
    {
        // IO Logic
        window.poll_input();

        // Make sure tha the mouse events aren't happneing in the UI
        if(io.WantCaptureMouse == false)
        {
            if(window.left_mouse_button_is_pressed())
            {
                if(mouse_is_being_held_down)
                {
                    // Take care of x rotations
                    start_x_position = current_x_position;
                    current_x_position = window.mouse_x_position();

                    if(current_x_position - start_x_position >= 2.0f)
                    {
                        cube_angles.x +=  1.0f;
                        rotation = glm::rotate(rotation, glm::radians(1.0f), y_axis);
                    }
                    else if(current_x_position - start_x_position <= -2.0f)
                    {
                        cube_angles.x += -1.0f;
                        rotation = glm::rotate(rotation, glm::radians(-1.0f), y_axis);
                    }

                    if(cube_angles.x >= 360.0f || cube_angles.x <= -360.0f)
                    {
                        cube_angles.x = 0.0f;
                    }

                    // Take care of y rotations
                    start_y_position = current_y_position;
                    current_y_position = window.mouse_y_position();

                    if(current_y_position - start_y_position >= 2.0f)
                    {
                        cube_angles.y +=  1.0f;
                        rotation = glm::rotate(rotation, glm::radians(1.0f), x_axis);
                    }
                    else if(current_y_position - start_y_position <= -2.0f)
                    {
                        cube_angles.y += -1.0f;
                        rotation = glm::rotate(rotation, glm::radians(-1.0f), x_axis);
                    }

                    if(cube_angles.y >= 360.0f || cube_angles.y <= -360.0f)
                    {
                        cube_angles.y = 0.0f;
                    }
                }
                else
                {
                    start_x_position = window.mouse_y_position();
                    mouse_is_being_held_down = true;
                }
            }
            else
            {
                mouse_is_being_held_down = false;
            }
        }

        // GUI Logic
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Cube Stats");

            ImGui::Text("Rotation: %.2f | %.2f | %.2f", cube_angles.x, cube_angles.y, cube_angles.z);


            ImGui::Separator();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Render Logic
        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        texture.set_active_texture(GL_TEXTURE0);
        texture.bind();

        program.use();

        model = transformation * rotation * scale;
        mvp = projection * view * model;

        program.set_uniform_mat4("mvp", mvp);

        buffer_controller.bind();
        buffer_controller.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap the windows
        window.swap_buffers();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return EXIT_SUCCESS;
}
