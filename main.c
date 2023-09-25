#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "libs/matrizes.h"
#include "libs/arquivos.h"

#include "libs/glad.h"
#include <GLFW/glfw3.h>


#define WIDTH 640.0f
#define HEIGHT 480.0f

#define X 1
#define Y 2
#define Z 3




MatrizF *color;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    //Exemplo de código para interpretar o botão Escape sendo pressionado e fechar a janela
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (action == GLFW_PRESS) {
        switch(key){
            case GLFW_KEY_R:{
                *getMF(color, 1, 1) = 1.0f;
                *getMF(color, 1, 2) = 0.0f;
                *getMF(color, 1, 3) = 0.0f;
                break;
            }
            case GLFW_KEY_B:{
                *getMF(color, 1, 1) = 0.0f;
                *getMF(color, 1, 2) = 0.0f;
                *getMF(color, 1, 3) = 1.0f;
                break;
            }
            case GLFW_KEY_G:{
                *getMF(color, 1, 1) = 0.0f;
                *getMF(color, 1, 2) = 1.0f;
                *getMF(color, 1, 3) = 0.0f;
                break;
            }case GLFW_KEY_J:{
                *getMF(color, 1, 1) = 1.0f;
                *getMF(color, 1, 2) = 0.8f;
                *getMF(color, 1, 3) = 0.19f;
                break;
            }case GLFW_KEY_SPACE:{

                // testes e coisas sem nexo

//                printf("\n");
                MatrizF* rotacional = matrizRotacional2D(90, 3);

//                printf("\n");
//                printaMatriz(color);
//                printf("\n");
//                printaMatriz(rotacional);

                color = multiplicarMatriz(color, rotacional);

//                printf("\n");
//                printaMatriz(color);

                freeM(rotacional);

                break;
            }
        }
    }

}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


int main() {

    //char* texto = openFile("../res/Poligonos.txt");
    //printf("%s\n", texto);

    printFileTest("../res/Poligonos.txt");

    //Preparando matrizes

    MatrizF *mat = criarMatrizFP(3, 3);
    float matriz[3][3] = {{WIDTH / 4, HEIGHT / 4, 0},
                          {WIDTH / 4 * 3, HEIGHT / 4, 0},
                          {WIDTH / 4 * 3, HEIGHT / 4 * 3, 0}};
    mat->p = (float *) &matriz;


    MatrizF *quadrado = criarMatrizFP(4, 3);
    float matriza[4][3] = {{-WIDTH / 4, HEIGHT / 4 * 3, 0},
                           {-WIDTH / 4, HEIGHT / 4},
                           {-WIDTH / 4 * 3, HEIGHT / 4},
                           {-WIDTH / 4 * 3, HEIGHT / 4 * 3}};
    quadrado -> p = (float *) &matriza;


    MatrizF* rotacao = matrizRotacional2D(0.5f, 3);


    MatrizF* pontoCentral = criarMatrizFP(3, 3);
    float matriz2[3][3] = {{WIDTH / 2, HEIGHT / 2, 0},
                           {WIDTH / 2, HEIGHT / 2, 0},
                           {WIDTH / 2, HEIGHT / 2, 0}};
    pontoCentral->p = (float *) &matriz2;


    color = criarMatrizF(1, 3);
    *getMF(color, 1, 1) = 1.0f;
    *getMF(color, 1, 2) = 0.0f;
    *getMF(color, 1, 3) = 0.0f;

    //printaMatriz(mat);


    //Preparar openGL

    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //Configurar versão mínima de OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //Criar janela
    window = glfwCreateWindow(WIDTH, HEIGHT, "Janela", NULL, NULL);
    if (!window)
    {
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glOrtho(-WIDTH, WIDTH, -HEIGHT, HEIGHT, -1, 1);

    //Iniciar Looping da janela até que a mesma seja fechada
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        int i;

        glClear(GL_COLOR_BUFFER_BIT);

        subtrairMatriz(mat, pontoCentral);
        mat = multiplicarMatriz(mat, rotacao);
        somarMatriz(mat, pontoCentral);


        glColor3f(
                fabs(*getMF(color, 1, 1)),
                fabs(*getMF(color, 1, 2)),
                fabs(*getMF(color, 1, 3)));
        glBegin(GL_TRIANGLES);
        glVertex2f(*getMF(mat, 1, X), *getMF(mat, 1, Y));
        glVertex2f(*getMF(mat, 2, X), *getMF(mat, 2, Y));
        glVertex2f(*getMF(mat, 3, X), *getMF(mat, 3, Y));
        glEnd();

        glColor3f(0, 0, 1);
        glBegin(GL_QUADS);
        glVertex2f(*getMF(quadrado, 1, X), *getMF(quadrado, 1, Y));
        glVertex2f(*getMF(quadrado, 2, X), *getMF(quadrado, 2, Y));
        glVertex2f(*getMF(quadrado, 3, X), *getMF(quadrado, 3, Y));
        glVertex2f(*getMF(quadrado, 4, X), *getMF(quadrado, 4, Y));
        glEnd();

//        glColor3f(0.0f, 1.0f, 0.0f);
//        inserirPoligono(poligonoSuperior);

        glfwSwapBuffers(window);
    }


    //Finalizar Programa

    //desalocar variáveis
    freeM(mat);
    freeM(pontoCentral);
    freeM(color);
    freeM(quadrado);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

//void inserirPoligono(Poligono poly){
//    glBegin(GL_TRIANGLES);
//    glVertex2f(poly.v1->x, poly.v1->y);
//    glVertex2f(poly.v2->x, poly.v2->y);
//    glVertex2f(poly.v3->x, poly.v3->y);
//    glEnd();
//}


