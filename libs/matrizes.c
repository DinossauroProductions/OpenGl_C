#include "matrizes.h"

int testarMultiplicassao(){

    //inicializar matrizes

    MatrizF *mat1 = criarMatrizF(3, 3);
    free(mat1 -> p);
    int matriz[3][3] = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    mat1->p = (float *) &matriz;

    MatrizF *mat2 = criarMatrizF(3, 3);
    free(mat2 -> p);
    int matris[3][3] = {{1, 2, 3},
                         {4, -5, 6},
                         {7, 8, 9}};
    mat2->p = (float *) &matris;

    //multiplicar

    MatrizF *matrizProduto = multiplicarMatriz(mat1, mat2);

    printaMatriz(mat1);

    printf("\n");

    printaMatriz(mat2);

    printf("\n");

    printaMatriz(matrizProduto);

    //limpar memória

    free(mat1);
    free(mat2);
    free(matrizProduto);

    return 0;
}

//Função de testes, pode ser eliminada. A intenção é chamar esta a partir do main para
int testarDeterminante(){
    MatrizF *mat = criarMatrizFP(4, 4);

    if(mat == NULL)
        printf("Impossível alocar matriz");

    int vetor[4][4] = {{1, 2, 3, -1},
                       {-4, 5, 6, -1},
                       {7, 8, 9, -1},
                       {60, 30, 7, -1}};

    mat -> p = (float *) &vetor;

    printf("Matriz:\n");
    printaMatriz(mat);

    printf("\nDeterminante: %f\n", calcularDeterminante(mat));

    //free(mat->p);
    free(mat);

    return 0;
}



//Cria e inicializa como 0 todos os elementos de
//uma matriz de tantas colunas e tantas linhas
MatrizF* criarMatrizF(int linhas, int colunas){

    MatrizF *mat = criarMatrizFP(linhas, colunas);

    float *p;
    p = (float*) malloc(sizeof(float) * colunas * linhas);

    mat -> p = p;

    zerarMatriz(mat);

    return mat;

}


//Cria a matriz e não inicializa seus valores, ficando a cargo do usuário alocar e inicializar os valores.
MatrizF* criarMatrizFP(int linhas, int colunas){
    //Verificar se o tamanho inserido é válido
    if(colunas <= 0 || linhas <= 0 || colunas > 1000 || linhas > 1000){
        return NULL;
    }

    //Criar a struct da matriz
    MatrizF* mat = (MatrizF*) malloc(sizeof(MatrizF));

    mat -> colunas = colunas;
    mat -> linhas = linhas;

    return mat;
}

MatrizF* criarMatrizFile(char* path, char* nome){



}

void zerarMatriz(MatrizF *mat){
    redefinirMatriz(mat, 0);
}

void redefinirMatriz(MatrizF *mat, float valor){
    for(int linha = 1; linha <= mat -> linhas; linha++){
        for(int coluna = 1; coluna <= mat -> colunas; coluna++){
            *getMF(mat, linha, coluna) = valor;
        }
    }
}

//Libera o espaço de memória referente à matriz.
void freeM(MatrizF* mat){
    free(mat->p);
    free(mat);
}

//retorna um valor
float* getMF(MatrizF *mat, int linha, int coluna){
    float *po = mat -> p + ((linha - 1) * mat -> colunas) + (coluna - 1);
    //printf("\ngetValI: %d, %d\n", mat-> p, po);
    return po;
}

float calcularDeterminante(MatrizF *mat){
    if(mat-> colunas != mat-> linhas  ||  mat->colunas <= 0 || mat-> linhas <= 0){
        printf("\nImpossivel calcular determinante: valores de matriz invalidos");
        return 0;
    }
    
    if(mat -> colunas == 1)
        return *(mat -> p);

    else if(mat-> colunas == 2 && mat-> linhas == 2){
        //método de cálculo de matrizes 2x2 (essencial para quebrar o loop recursivo)
        return
                *getMF(mat, 1, 1) * *getMF(mat, 2, 2) -
        *getMF(mat, 1, 2) * *getMF(mat, 2, 1);
    }

//    else if(mat-> colunas == 3 && mat-> linhas == 3){
//        //método de laplace para as matrizes 3x3
//        return (int) (
//                *getValI(mat, 1, 1) * *getValI(mat, 2, 2) * *getMF(mat, 3, 3) +
//                *getValI(mat, 1, 2) * *getValI(mat, 2, 3) * *getMF(mat, 3, 1) +
//                *getValI(mat, 1, 3) * *getValI(mat, 2, 1) * *getMF(mat, 3, 2) -
//
//                *getValI(mat, 1, 3) * *getValI(mat, 2, 2) * *getMF(mat, 3, 1) -
//                *getValI(mat, 1, 1) * *getValI(mat, 2, 3) * *getMF(mat, 2, 2) -
//                *getValI(mat, 1, 2) * *getMF(mat, 2, 1) * *getValI(mat, 3, 3)
//        );
//    }

    else{
        //método recursivo
        float det = 0;
        for(int i = 1; i <= mat->colunas; i++){
            int sinal = 1;
            if(i % 2 == 0){
                sinal = -1;
                //printf("Sinal invertido");
            }
            det += (float) sinal * (*getMF(mat, 1, i)) * calcularCofator(mat, i, 1);
        }
        return det;
    }
}

float calcularCofator(MatrizF *mat, int x, int y){

    if(y != 1 || x < 1 || x > mat-> colunas){

        printf("\nImpossivel calcular cofator: valores de entrada invalids: %d %d", x, y);
        return 0;
    }

    MatrizF *temp = criarMatrizF(mat->colunas - 1, mat-> linhas - 1);

    int iMenor = 1, jMenor = 1;

    for(int linha = 1; linha <= mat -> linhas; linha++){
        if(linha == y)
            continue;
        for(int coluna = 1; coluna <= mat -> colunas; coluna++){

            if(coluna == x){
                continue;
            }
            float *ponto = getMF(mat, linha, coluna);

            *getMF(temp, iMenor, jMenor) = *ponto;
            jMenor++;

        }
        iMenor++;
        jMenor = 1;
    }

    printf("\n");


    printf("Menor:\n");

    printaMatriz(temp);

    float det = calcularDeterminante(temp);
    free(temp);
    //printf("Determinante do menor: %d\n", det);

    return det;

}

//soma a mat1 e mat2, e armazena o resultado na mat1.
int somarMatriz(MatrizF *mat1, MatrizF *mat2){

    if(mat1 -> linhas != mat2 -> linhas || mat1 -> colunas != mat2 -> colunas){
        return -1;
    }

    for(int linha = 1; linha <= mat1 -> linhas; linha++){
        for(int coluna = 1; coluna <= mat1 -> colunas; coluna++){

            *getMF(mat1, linha, coluna) += *getMF(mat2, linha, coluna);

        }
    }
    return 0;

}

int subtrairMatriz(MatrizF *mat1, MatrizF *mat2){

    if(mat1 -> linhas != mat2 -> linhas || mat1 -> colunas != mat2 -> colunas){
        return -1;
    }

    for(int linha = 1; linha <= mat1 -> linhas; linha++){
        for(int coluna = 1; coluna <= mat1 -> colunas; coluna++){

            *getMF(mat1, linha, coluna) -= *getMF(mat2, linha, coluna);

        }
    }
    return 0;

}

MatrizF* multiplicarMatriz(MatrizF *mat1, MatrizF *mat2){

    if(mat1 -> colunas != mat2 -> linhas){
        printf("\nImpossivel multiplicar matrizes: tamanhos de matrizes incompatíveis: %dx%d %dx%d\n", mat1->linhas, mat1->colunas, mat2->linhas, mat2->colunas);
        return NULL;
    }

    MatrizF *resultante = criarMatrizF(mat1->linhas, mat2->colunas);

    for(int linha = 1; linha <= resultante -> linhas; linha++){
        for(int coluna = 1; coluna <= resultante -> colunas; coluna++){

            for(int i = 1; i <= resultante -> colunas; i++){
                //printf("%d", *getMF(mat1, linha, i) * *getMI(mat2, i, coluna));
                *getMF(resultante, linha, coluna) +=
                        *getMF(mat1, linha, i) * *getMF(mat2, i, coluna);
            }

        }
    }

    return resultante;

}

//Cria uma matriz de rotação pelo ângulo com o tamanho desejado. Caso seja 2, será normalmente, caso seja 3, será completada com 0s e 1 na diagonal.
MatrizF* matrizRotacional2D(float angulo, int tamanho){

    if(tamanho != 2 && tamanho != 3)
        return NULL;

    MatrizF *matR = criarMatrizF(3, 3);

    angulo = angulo / 180 * M_PI;

    float cosseno = cos(angulo);
    float seno = sin(angulo);

    *getMF(matR, 1, 1) = cosseno;
    *getMF(matR, 1, 2) = seno;

    *getMF(matR, 2, 1) = - seno;
    *getMF(matR, 2, 2) = cosseno;

    if(tamanho == 3)
        *getMF(matR, 3, 3) = 1;

    return matR;

}

void printaMatriz(MatrizF *mat){
    for(int linha = 1; linha <= mat -> linhas; linha++){
        for(int coluna = 1; coluna <= mat -> colunas; coluna++){
            printf("%.1f ", *getMF(mat, linha, coluna));
        }
        printf("\n");
    }
}

