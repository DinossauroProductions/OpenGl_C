cmake_minimum_required(VERSION 3.25)
project(openGL C)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)

add_executable(openGL main.c libs/glad.c libs/glad.h libs/matrizes.h libs/matrizes.c libs/arquivos.c libs/arquivos.h)

target_link_libraries(openGL
        glfw
        GLEW
        OpenGL::GL
        GLU
        m
)

#target_link_libraries(openGL m)