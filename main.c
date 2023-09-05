#define GLFW_INCLUDE_NONE
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glew.h>
#include <glad.h>
#include <GLFW/glfw3.h>







static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{



    //Exemplo de código para interpretar o botão Escape sendo pressionado e fechar a janela
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


int main() {

    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    //Inicializar GLFW
    if (!glfwInit())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //Configurar versão mínima de OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //Criar janela
    window = glfwCreateWindow(640, 480, "Janela", NULL, NULL);
    if (!window)
    {
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    //Iniciar Looping da janela até que a mesma seja fechada
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }


    //Finalizar Programa
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


