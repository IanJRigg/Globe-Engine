cmake_minimum_required(VERSION 3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src/)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib/)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test/)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

# Application Configuration
###############################################################################
set(PROJECT_NAME app)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES
    ${SRC_DIR}/camera.cpp
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/mesh.cpp
    ${SRC_DIR}/planet-generator.cpp
    ${SRC_DIR}/program.cpp
    ${SRC_DIR}/texture.cpp
    ${SRC_DIR}/window.cpp
    ${SRC_DIR}/raycaster.cpp
)

set(HEADER_FILES
    ${SRC_DIR}/camera.h
    ${SRC_DIR}/fragment-shader.h
    ${SRC_DIR}/vertex-shader.h
    ${SRC_DIR}/mesh.h
    ${SRC_DIR}/planet-generator.h
    ${SRC_DIR}/program.h
    ${SRC_DIR}/texture.h
    ${SRC_DIR}/window.h
    ${SRC_DIR}/raycaster.h

    # GLAD Includes
    ${INCLUDE_DIR}/glad/glad.h

    # IMGUI Includes
    ${INCLUDE_DIR}/imgui/imconfig.h
    ${INCLUDE_DIR}/imgui/imgui.h
    ${INCLUDE_DIR}/imgui/imgui_impl_glfw.h
    ${INCLUDE_DIR}/imgui/imgui_impl_opengl3.h
    ${INCLUDE_DIR}/imgui/imgui_internal.h
    ${INCLUDE_DIR}/imgui/imstb_rectpack.h
    ${INCLUDE_DIR}/imgui/imstb_textedit.h
    ${INCLUDE_DIR}/imgui/imstb_truetype.h
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
        ${INCLUDE_DIR}
        ${INCLUDE_DIR}/imgui
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        glm
        glfw
        ${LIB_DIR}/bin/libglad.a
        ${LIB_DIR}/bin/libimgui.a
)


# Test Suite Configuration (Commented out for now until there are worthy tests)
###############################################################################
#add_subdirectory(test)