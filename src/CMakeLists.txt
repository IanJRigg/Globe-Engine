cmake_minimum_required(VERSION 3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Application Configuration
###############################################################################
set(PROJECT_NAME app)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES
    glad.c
    camera.cpp
    main.cpp
    mesh.cpp
    planet-generator.cpp
    program.cpp
    texture.cpp
    window.cpp
    ../${LIB_DIR}/imgui/imgui.cpp
    ../${LIB_DIR}/imgui/imgui_demo.cpp
    ../${LIB_DIR}/imgui/imgui_draw.cpp
    ../${LIB_DIR}/imgui/imgui_impl_glfw.cpp
    ../${LIB_DIR}/imgui/imgui_impl_opengl3.cpp
    ../${LIB_DIR}/imgui/imgui_widgets.cpp
)

set(HEADER_FILES
    camera.h
    fragment-shader.h
    vertex-shader.h
    mesh.h
    planet-generator.h
    program.h
    texture.h
    window.h
    ../${INCLUDE_DIR}/imgui/imconfig.h
    ../${INCLUDE_DIR}/imgui/imgui.h
    ../${INCLUDE_DIR}/imgui/imgui_impl_glfw.h
    ../${INCLUDE_DIR}/imgui/imgui_impl_opengl3.h
    ../${INCLUDE_DIR}/imgui/imgui_internal.h
    ../${INCLUDE_DIR}/imgui/imstb_rectpack.h
    ../${INCLUDE_DIR}/imgui/imstb_textedit.h
    ../${INCLUDE_DIR}/imgui/imstb_truetype.h
)

find_package(glm REQUIRED)
find_package(glfw3  REQUIRED)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        # C++ version information
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO

        # Public Header file location
        PUBLIC_HEADER "${HEADER_FILES}"
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${OPEN_GL_INCLUDE_DIR}
        ../${INCLUDE_DIR}/
        ../${INCLUDE_DIR}/imgui
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        glm
        glfw
)