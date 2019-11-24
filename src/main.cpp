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
#include "program.h"
#include "texture.h"
#include "mesh.h"
#include "window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <cmath>

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

void render_cube()
{
    Window window("Render Cube", 768UL, 1024UL);
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

    Mesh mesh;
    mesh.bind();
    mesh.load_vertex_buffer(cube_vertices);
    mesh.set_vertex_buffer_attribute(0, 3, 0);
    mesh.set_vertex_buffer_attribute(1, 3, 3);
    mesh.set_vertex_buffer_attribute(2, 2, 6);

    Texture_2D texture;
    texture.bind();
    texture.load_jpg("textures/container.jpg");
    texture.set_s_axis_to_repeat();
    texture.set_t_axis_to_repeat();
    texture.set_minifying_filter_to_nearest();
    texture.set_magnifying_filter_to_nearest();

    Program program;
    program.load_vertex_shader("shaders/vertex/cube.vert");
    program.load_fragment_shader("shaders/fragment/cube.frag");
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

        // UI Logic
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

void generate_subdivided_tetrahedron(std::vector<float>& vertices, std::vector<uint32_t>& indices, const uint32_t level)
{
    const float root_two_over_three = sqrt(2.0) / 3.0;
    const float one_third = -(1.0 / 3.0);
    const float root_six_over_three = sqrt(6.0) / 3.0;

    vertices.reserve(pow(4.0, level + 1));
}

void subdivide(std::vector<float>& vertices, std::vector<uint32_t>& indices, const uint32_t level)
{
    if(level > 0)
    {
        subdivide(vertices, indices, level - 1);
    }
    else
    {

    }
}

void render_sphere_via_subdivided_tetrahedron()
{
    Window window("Subdivision Surfaces Sphere", 768UL, 1024UL);
    window.enable_vsync();
    window.enable_depth_test();
    // window.enable_backface_culling();

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
    generate_subdivided_tetrahedron(vertices, indices, 1);

    Mesh mesh;
    mesh.bind();
    mesh.load_vertex_buffer(vertices);
    mesh.load_index_buffer(indices);
    mesh.set_vertex_buffer_attribute(0, 3, 0); // Mark the X/Y/Z vertices

    Program program;
    program.load_vertex_shader("shaders/vertex/cube-map.vert");
    program.load_fragment_shader("shaders/fragment/cube-map.frag");
    program.link();

    program.use();

    glm::mat4 transformation(1.0f);
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

    while(no_signals_have_been_raised() && window.should_not_close())
    {
        // IO Logic
        window.poll_input();

        // Make sure tha the mouse events aren't happneing in the UI
        if(io.WantCaptureMouse == false)
        {

        }

        // UI Logic
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Hello World!");

            ImGui::End();
        }

        // Render Logic
        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        program.use();

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

void generate_cube_with_subdivisions(std::vector<float>& vertices,
                                     std::vector<uint32_t>& indices,
                                     const uint32_t number_of_subdivisions)
{
    const uint32_t vertices_per_side = number_of_subdivisions + 2;

    vertices.resize(vertices_per_side * vertices_per_side * 3, 0.0f);

    float step = 1.0 / (vertices_per_side - 1UL);
    uint32_t n = 0UL;

    for(uint32_t i = 0; i < vertices_per_side; i++)
    {
        for(uint32_t j = 0; j < vertices_per_side; j++)
        {
            vertices.at(n + 0UL) = j * step; // X
            vertices.at(n + 1UL) = i * step; // Y
            vertices.at(n + 2UL) = 0.0f;     // Z

            //std::cout << j * step << " " << i * step << " " << 0.0 << std::endl;

            n += 3UL;
        }
    }

    n = 0UL;


    // Number of Subdivisions: 1

    // Vertices
    // 6 7 8
    // 3 4 5
    // 0 1 2

    // Indices
    // 0 1 4   i = 0; j = 0;
    // 0 4 3   i = 0; j = 0l
    // 1 2 5   i = 0; j = 1;
    // 1 5 4   i = 0; j = 1;
    // 3 4 7   i = 1; j = 0;
    // 3 7 6   i = 1; j = 0;
    // 4 5 8   i = 1; j = 1;
    // 4 8 7   i = 1; j = 1;


    // NUmber of Subdivisions: 2

    // C D E F
    // 8 9 A B
    // 4 5 6 7
    // 0 1 2 3

    // Indices
    // 0 1 5   i = 0; j = 0;
    // 0 5 4   i = 0; j = 0;
    // 1 2 6   i = 0; j = 1;
    // 1 6 5   i = 0; j = 1;
    // 2 3 7   i = 0; j = 2;
    // 2 7 6   i = 0; j = 2;
    // 4 5 9   i = 1; j = 0;
    // 4 9 8   i = 1; j = 0;
    // 5 6 A   i = 1; j = 1;
    // 5 A 9   i = 1; j = 1;
    // 6 7 B   i = 1; j = 2;
    // 6 B A   i = 1; j = 2;
    // 8 9 D   i = 2; j = 0;
    // 8 D C   i = 2; j = 0;
    // 9 A E   i = 2; j = 1;
    // 9 E D   i = 2; j = 1;
    // A B F   i = 2; j = 2;
    // A F E   i = 2; j = 2;

    std::cout << std::endl;

    indices.resize((vertices_per_side - 1) * (vertices_per_side - 1) * 6, 0UL);

    for(uint32_t i = 0; i < vertices_per_side - 1; ++i)
    {
        for(uint32_t j = 0; j < vertices_per_side - 1; ++j)
        {
            indices.at(n + 0UL) = i * vertices_per_side + j;       // X
            indices.at(n + 1UL) = i * vertices_per_side + j + 1UL; // Y
            indices.at(n + 2UL) = i * vertices_per_side + j + (vertices_per_side + 1UL); // Z

            // std::cout << i * vertices_per_side + j << " "
            //           << i * vertices_per_side + j + 1UL << " "
            //           << i * vertices_per_side + j + (vertices_per_side + 1UL) << std::endl;

            indices.at(n + 3UL) = i * vertices_per_side + j;       // X
            indices.at(n + 4UL) = i * vertices_per_side + j + (vertices_per_side + 1UL); // Y
            indices.at(n + 5UL) = i * vertices_per_side + j + (vertices_per_side + 0UL); // Z

            // std::cout << i * vertices_per_side + j << " "
            //           << i * vertices_per_side + j + (vertices_per_side + 1UL) << " "
            //           << i * vertices_per_side + j + (vertices_per_side + 0UL) << std::endl;

            n += 6UL;
        }
    }
}

void render_sphere_via_cube_map()
{
    Window window("Cube Map Sphere", 768UL, 1024UL);
    window.enable_vsync();
    window.enable_depth_test();
    window.enable_backface_culling();
    window.enable_wireframe();

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
    generate_cube_with_subdivisions(vertices, indices, 100);

    Mesh mesh;
    mesh.bind();
    mesh.load_vertex_buffer(vertices);
    mesh.load_index_buffer(indices);
    mesh.set_vertex_buffer_attribute(0, 3, 0); // Mark the X/Y/Z vertices


    Program program;
    program.load_vertex_shader("shaders/vertex/cube-map.vert");
    program.load_fragment_shader("shaders/fragment/cube-map.frag");
    program.link();

    program.use();

    Camera camera;
    camera.position.z = 2.0f;

    glm::mat4 transformation(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    glm::mat4 model(1.0f);
    glm::mat4 view = camera.look_at();
    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom()), window.aspect_ratio(), 0.1f, 100.0f);

    glm::mat4 mvp(1.0f);

    while(no_signals_have_been_raised() && window.should_not_close())
    {
        // IO Logic
        window.poll_input();

        // Make sure tha the mouse events aren't happneing in the UI
        if(io.WantCaptureMouse == false)
        {

        }

        // UI Logic
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Hello World!");

            ImGui::SliderFloat("Z Position", &camera.position.z, -10.0f, 10.0f);

            ImGui::End();
        }

        std::cout << camera.position.z << std::endl;

        // Render Logic
        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        program.use();

        view = camera.look_at();
        projection = glm::perspective(glm::radians(camera.zoom()), window.aspect_ratio(), 0.1f, 100.0f);

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

void render_sphere_via_geographic_grid()
{
    Window window("Geographic Grid Sphere", 768UL, 1024UL);
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

    Mesh mesh;
    mesh.bind();
    // Generate vector of vertices for the cube
    // Front face:
    // 0 0.0, 0.0, 0.0
    // 1 1.0, 0.0, 0.0
    // 2 1.0, 1.0, 0.0
    // 3 0.0, 1.0, 0.0

    // Indices are: 0 1 2 / 0 2 3

    // Right face
    // 1 1.0, 0.0,  0.0,
    // 4 1.0, 0.0, -1.0,
    // 5 1.0, 1.0, -1.0,
    // 2 1.0, 1.0,  0.0

    // Indices are: 1 4 5 / 1 5 2

    // Back Face
    // 4 1.0, 0.0, -1.0
    // 6 0.0, 0.0, -1.0
    // 7 0.0, 1.0, -1.0
    // 5 1.0, 1.0, -1.0

    // Indices are 4 6 7 / 4 7 5

    // Left Face
    // 6 0.0, 0.0, -1.0
    // 0 0.0, 0.0,  0.0
    // 3 0.0, 1.0,  0.0
    // 7 0.0, 1.0, -1.0

    // Indices are 6 0 3 / 6 3 7

    // Top Face
    // 3 0.0, 1.0,  0.0
    // 2 1.0, 1.0,  0.0
    // 5 1.0, 1.0, -1.0
    // 7 0.0, 1.0, -1.0

    // Indices are 3 2 5 / 3 5 7

    // Bottom Face
    // 0 0.0, 0.0,  0.0
    // 1 1.0, 0.0,  0.0
    // 4 1.0, 0.0, -1.0
    // 6 0.0, 0.0, -1.0

    // Indices are 0 1 4 / 0 4 6


    // Index generation is very simple... 0,1,2 / 0,2,3 for each ID'd square

    // 0 0.0, 0.0,  0.0
    // 1 1.0, 0.0,  0.0
    // 2 1.0, 1.0,  0.0
    // 3 0.0, 1.0,  0.0
    // 4 0.0, 0.0, -1.0
    // 5 1.0, 0.0, -1.0
    // 6 1.0, 1.0, -1.0
    // 7 0.0, 1.0, -1.0

    // Two passes
    // First generates all of the vertices and loads them into a buffer
    // Second pass generates all of the indices and loads them into a buffer

    Program program;
    program.load_vertex_shader("shaders/vertex/cube-map.vert");
    program.load_fragment_shader("shaders/fragment/cube-map.frag");
    program.link();

    program.use();

    glm::mat4 transformation(1.0f);
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

    while(no_signals_have_been_raised() && window.should_not_close())
    {
        // IO Logic
        window.poll_input();

        // Make sure tha the mouse events aren't happneing in the UI
        if(io.WantCaptureMouse == false)
        {

        }

        // UI Logic
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Hello World!");

            ImGui::End();
        }

        // Render Logic
        window.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        window.clear_buffer_bits();

        program.use();

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

    // render_sphere_via_subdivided_tetrahedron();
    render_sphere_via_cube_map();

    return EXIT_SUCCESS;
}
