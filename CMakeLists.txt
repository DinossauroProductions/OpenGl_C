cmake_minimum_required(VERSION 3.25)
project(openGL C)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)

add_executable(openGL main.c glad.c glad.h)

target_link_libraries(openGL
        glut
        glfw
        GLEW
        OpenGL::GL
        GLU
)