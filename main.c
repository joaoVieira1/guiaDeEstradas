#include "lib.h"

int main(){

    double **matrix;

    printf("-------------------------\n");
    printf("     GUIA DE ESTRADAS   \n");
    printf("-------------------------\n");

    matrix = criarMatrix();
    inicializarMatrix(matrix);
    
    menu(matrix);

    free(matrix);
    
    printf("-------------------------\n");
    printf("        ATE LOGO!        \n");
    printf("-------------------------\n");

    return 0;
}