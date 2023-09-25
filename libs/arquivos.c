
#include "arquivos.h"

char* openFile(char* path){

    //char *ponteiro = malloc(sizeof(char)* 100);

    //printf("%s", getcwd(ponteiro, sizeof(char)* 100));

    FILE *file;

    file = fopen(path, "r");

    if(file == NULL){
        printf("Impossível carregar arquivo: \"%s\"", path);
        return NULL;
    }

    struct stat st;
    long length = stat(path, &st) == 0 ? st.st_size : 0L;

    //printf("%d  ", stat(path, &st));

    char* texto = malloc((length+1));

    fgets(texto, (int)length, file);

    texto[length] = '\0';

    fclose(file);

    return texto;
}

void printFileTest(char* path){

    struct stat st;
    stat(path, &st);

    char* file = openFile(path);

    for(int i = 0; i < st.st_size; i++){
        printf("%d ", file[i]);
    }

    free(file);

}