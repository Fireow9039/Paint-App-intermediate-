cmake_minimum_required(VERSION 3.16)
project(Paint_App_Graphic)

set(CMAKE_CXX_STANDARD 20)

# Let CMake find SFML 2
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Paint_App_Graphic main.cpp)
target_link_libraries(Paint_App_Graphic sfml-graphics sfml-window sfml-system)
