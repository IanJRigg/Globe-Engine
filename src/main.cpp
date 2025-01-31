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

#include "camera.h"
#include "planet-generator.h"
#include "program.h"
#include "raycaster.h"
#include "texture.h"
#include "mesh.h"
#include "window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <cmath>
#include <iomanip>

std::vector<std::string> globe_faces
{
    "textures/political/right.png",
    "textures/political/left.png",
    "textures/political/top.png",
    "textures/political/bottom.png",
    "textures/political/front.png",
    "textures/political/back.png"
};

void render_sphere_via_cube_map()
{
    Window window("Cube Map Sphere", 1534UL, 2048UL);
    window.enable_vsync();
    window.enable_depth_test();
    window.enable_backface_culling();
    //window.enable_wireframe();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    window.register_imgui();
    ImGui_ImplOpenGL3_Init("#version 410 core");

    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    generate_cube_with_subdivisions(vertices, indices, 256);

    Mesh mesh;
    mesh.bind();
    mesh.load_vertex_buffer(vertices);
    mesh.load_index_buffer(indices);
    mesh.set_vertex_buffer_attribute(0, 3, 0); // Mark the X/Y/Z vertices

    Texture texture;
    texture.bind_with_cube_map_as_target();
    texture.load_cube_map_png(globe_faces);
    texture.set_magnifying_filter_to_linear();
    texture.set_minifying_filter_to_linear();
    texture.set_s_axis_to_clamp_to_edge();
    texture.set_t_axis_to_clamp_to_edge();
    texture.set_r_axis_to_clamp_to_edge();

    Program program;
    program.load_vertex_shader("shaders/vertex/cube-map.vert");
    program.load_fragment_shader("shaders/fragment/cube-map.frag");
    program.link();

    program.use();
    program.set_uniform_integer("texture1", 0);

    Camera camera;
    camera.set_distance_to_near_plane(0.1f);
    camera.set_distance_to_far_plane(10.0f);

    glm::mat4 transformation(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    glm::mat4 model(1.0f);
    glm::mat4 view = camera.view_matrix();
    glm::mat4 projection = camera.projection_matrix(window.aspect_ratio());

    glm::mat4 mvp(1.0f);

    bool mouse_is_being_held_down = false;

    double start_x_position = 0.0f;
    double current_x_position = 0.0f;

    double start_y_position = 0.0f;
    double current_y_position = 0.0f;

    float azimuth = 0.0f;
    float elevation = 0.0f;

    float fov = 90.0f;

    float near = 0.1f;
    float far = 100.0f;

    float hypotenuse = 2.0f;

    bool button_is_toggled = false;

    while(no_signals_have_been_raised() && window.should_not_close())
    {
        // IO Logic
        window.poll_input();

        // Make sure tha the mouse events aren't happneing in the UI
        if(io.WantCaptureMouse == false)
        {
            if(window.left_mouse_button_is_pressed())
            {
                glm::vec3 ray = screen_position_to_ray(window, camera);
                glm::vec3 point_on_sphere = instersection_of_ray_with_sphere(ray, camera.position);

                std::cout << "Longitude: " << asin(point_on_sphere.y) * (180.0f / M_PI) << std::endl;
                std::cout << "Latitude: " << atan(point_on_sphere.x / point_on_sphere.z) * (180.0f / M_PI) << std::endl;
                std::cout << std::endl;

                if(mouse_is_being_held_down)
                {
                    // Azimuth rotations
                    start_x_position = current_x_position;
                    current_x_position = window.mouse_x_position();

                    if(current_x_position - start_x_position >= 2.0f)
                    {
                        azimuth += 1.0f;
                    }
                    else if(current_x_position - start_x_position <= -2.0f)
                    {
                        azimuth -= 1.0f;
                    }

                    if(azimuth >= 360.0f || azimuth <= -360.0f)
                    {
                        azimuth = 0.0f;
                    }

                    // Take care of y rotations
                    start_y_position = current_y_position;
                    current_y_position = window.mouse_y_position();

                    if((current_y_position - start_y_position >= 2.0f) && (elevation < 80.0f))
                    {
                        elevation += 1.0f;
                    }
                    else if((current_y_position - start_y_position <= -2.0f) && (elevation > -80.0f))
                    {
                        elevation -= 1.0f;
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

        // UI Logic
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Hello World!");

            ImGui::SliderFloat("X Position", &camera.position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("Y Position", &camera.position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("Z Position", &camera.position.z, -10.0f, 10.0f);

            ImGui::SliderFloat("FOV", &fov, 0.0f, 180.0f);

            ImGui::SliderFloat("Near", &near, 0.0f, 1.0f);
            ImGui::SliderFloat("Far", &far, 0.0f, 100.0f);

            ImGui::SliderFloat("Hypotenuse", &hypotenuse, 1.0f, 5.0f);

            ImGui::End();
        }

        // Camera Logic
        {
            // Angle is the elevation
            camera.position.y = hypotenuse * sin(elevation * (M_PI / 180.0f));
            float horizontal_hypotenuse = hypotenuse * cos(elevation * (M_PI / 180.0f));

            // Use the azimuth for this position
            camera.position.x = horizontal_hypotenuse * cos(azimuth * (M_PI / 180.0f));
            camera.position.z = horizontal_hypotenuse * sin(azimuth * (M_PI / 180.0f));
        }

        // Render Logic
        window.clear_color(0.9f, 0.9f, 0.9f, 1.0f);
        window.clear_buffer_bits();

        // texture.set_active_texture(GL_TEXTURE0);
        // texture.bind();

        program.use();

        camera.set_fov(fov);

        view = camera.view_matrix();
        projection = camera.projection_matrix(window.aspect_ratio());

        model = transformation * rotation * scale;
        mvp = projection * view * model;

        program.set_uniform_mat4("mvp", mvp);

        mesh.bind();
        mesh.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap the windows
        window.swap_buffers();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main(int, char**)
{
    setup_signal_handlers();

    // render_cube();

    render_sphere_via_cube_map();

    return EXIT_SUCCESS;
}
