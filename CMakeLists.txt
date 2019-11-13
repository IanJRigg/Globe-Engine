cmake_minimum_required(VERSION 3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")

set(SRC_DIR src/)
set(LIB_DIR lib/)
set(TEST_DIR test/)
set(INCLUDE_DIR include/)

add_subdirectory(src)
add_subdirectory(test)