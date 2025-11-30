cmake_minimum_required(VERSION 4.2.0)

# Define the project name, version, and languages used (C and C++)
project(vehicalgraphics VERSION 0.1.0 LANGUAGES C CXX)

# Include CTest, which adds testing-related functionality
include(CTest)

find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)


# Enable the testing framework (lets you add tests with add_test later)
enable_testing()

# Create an executable named 'vehicalgraphics' built from app.cpp
add_executable(vehicalgraphics
    src/main.cpp
    src/glad.c
)

set(CMAKE_BUILD_TYPE Debug)


# Tell the compiler where GLAD headers are
target_include_directories(vehicalgraphics PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Set the C++ standard for this target to C++17 (for intellisense too)
set_property(TARGET vehicalgraphics PROPERTY CXX_STANDARD 17)

target_link_libraries(vehicalgraphics PRIVATE
    glfw
    glm::glm 
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
)

