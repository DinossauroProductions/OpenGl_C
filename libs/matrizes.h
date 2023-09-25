
//
// Created by guilherme on 19/09/23.
//

#ifndef OPENGL_MATRIZES_H
#define OPENGL_MATRIZES_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arquivos.h"

struct estrutura{
    float *p;
    int linhas, colunas;
}typedef MatrizF;

// Gerenciamento básico de Matrizes

MatrizF* criarMatrizF(int linhas, int colunas);
MatrizF* criarMatrizFP(int linhas, int colunas);
MatrizF* criarMatrizFile(char* path, char* nome);
void redefinirMatriz(MatrizF *mat, float valor);
void zerarMatriz(MatrizF *mat);
void freeM(MatrizF *mat);
float* getMF(MatrizF *mat, int linha, int coluna);

void printaMatriz(MatrizF* mat);

int somarMatriz(MatrizF *mat1, MatrizF *mat2);
int subtrairMatriz(MatrizF *mat1, MatrizF *mat2);
MatrizF* multiplicarMatriz(MatrizF *mat1, MatrizF *mat2);
float calcularCofator(MatrizF *mat, int x, int y);
float calcularDeterminante(MatrizF *mat);

MatrizF* matrizRotacional2D(float angulo, int tamanho);


#endif //OPENGL_MATRIZES_H
