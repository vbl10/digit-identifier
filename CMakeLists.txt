cmake_minimum_required(VERSION 3.5.0)
project(digit_identifier VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)  # Set C++17 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Make the standard required

file(GLOB SOURCES "src/*.cpp")

add_executable(digit_identifier ${SOURCES})

# Link X11 libraries to your executable
# Link libraries
target_link_libraries(digit_identifier
    PRIVATE
    X11
    GL
    pthread
    png
    stdc++fs
)
