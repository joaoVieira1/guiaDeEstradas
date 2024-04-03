#include "lib.h"

double **criarMatrix(){
    double **matrix = (double **) malloc(TAM * sizeof(double *));

    for(int i = 0; i < TAM; i++){
        matrix[i] = (double *) malloc(TAM * sizeof(double));
    }

    return matrix;
}

void liberarMatrix(double **matrix){
    for(int i = 0; i < TAM; i++){
        free(matrix[i]);
    }

    free(matrix);
}

void inicializarMatrix(double **matrix){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            matrix[i][j] = 0;
        }
    }
}

void mostrarMatrix(double **matrix){
    for(int i = 0; i < TAM; i++){
        printf("\n");
        for(int j = 0; j < TAM; j++){
            printf("%lf ", matrix[i][j]);
        }
    }
}

void cadastrarEstrada(double **matrix){
    int origem, destino;
    double distancia;

    printf("\nCadastrar Estrada: \n");

    printf("Origem: ");
    scanf("%d", &origem);

    while(origem < 0 || origem >= TAM){
        printf("Esta cidade nao existe, tente novamente: ");
        scanf("%d", &origem);
    }

    printf("Destino: ");
    scanf("%d", &destino);

    while(destino < 0 || destino >= TAM){
        printf("Esta cidade nao existe, tente novamente: ");
        scanf("%d", &destino);
    }

    printf("Distancia [KMs]: ");
    scanf("%lf", &distancia);

    while(distancia <= 0){
        printf("Distancia invalida, tente novamente: ");
        scanf("%lf", &distancia);
    }

    if(matrix[origem][destino] > 0 && matrix[origem][destino] > 0){
        printf("\nEsta estrada ja existe!\n");
    }else{
        matrix[origem][destino] = distancia;
        matrix[destino][origem] = distancia;
        printf("\nEstrada cadastrada com sucesso!\n\n");
    }
    
    
}

void verEstradas(double **matrix){
    int cidade;

    printf("\nVeja as estradas ligadas a cidade: ");
    scanf("%d", &cidade);

    while(cidade < 0 || cidade > 99){
        printf("Esta cidade nao existe, tente novamente: ");
        scanf("%d", &cidade);
    }

    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(i == cidade){
                if(matrix[i][j] > 0){
                    printf("\nCidade %d: estrada para cidade %d -> distancia: %.2lfkms\n\n", i, j, matrix[i][j]);
                }
            }
        }
    }
}

void consultarEstrada(double **matrix){
    int origem, destino;

    printf("\nConsultar estrada:\n");
    
    printf("Origem: ");
    scanf("%d", &origem);

    while(origem < 0 || origem >= TAM){
        printf("Esta cidade nao existe, tente novamente: ");
        scanf("%d", &origem);
    }

    printf("Destino: ");
    scanf("%d", &destino);

    while(destino < 0 || destino >= TAM){
        printf("Esta cidade nao existe, tente novamente: ");
        scanf("%d", &destino);
    }

    if(matrix[origem][destino] > 0){
        printf("\nEstrada encontrada!\n");
        printf("Cidade %d: estrada para cidade %d -> distancia: %.2lfkms\n\n", origem, destino, matrix[origem][destino]);
    }else{
        printf("\nEstrada nao encontrada!\n\n");
    }
}

void excluirEstrada(double **matrix){
    int origem, destino;

    printf("\nExcluir estrada: \n");

    printf("Origem: ");
    scanf("%d", &origem);

    while(origem < 0 || origem >= TAM){
        printf("Esta cidade nao existe, tente novamente: ");
        scanf("%d", &origem);
    }

    printf("Destino: ");
    scanf("%d", &destino);

    while(destino < 0 || destino >= TAM){
        printf("Esta cidade nao existe, tente novamente: ");
        scanf("%d", &destino);
    }

    matrix[origem][destino] = 0;
    matrix[destino][origem] = 0;

    printf("Estrada excluida com sucesso!\n\n");
}

int distanciaMin(int distancias[], int visitados[]){
    int min = INF; 
    int min_index;

    for (int v = 0; v < TAM; v++){
        if (visitados[v] == 0 && distancias[v] <= min){
            min = distancias[v]; 
            min_index = v;
        }
    }
        
    return min_index;
}

void mostrarCaminho(int prev[], int j){
    // Se j é a fonte
    if (prev[j] == -1){
        return;
    }

    mostrarCaminho(prev, prev[j]);

    printf(" <- %d\n", j);
}

void mostrarMenoresCaminhos(int distancias[], int prev[], int origem){
    printf("\nDe Para\t\tDistancia\tMenor caminho\n");
    for (int i = 0; i < TAM; i++) {
        if (distancias[i] != INF && i != origem) {
            printf("%d -> %d\t\t%dkms\t\t%d", origem, i, distancias[i], origem);
            mostrarCaminho(prev, i);
            printf("\n");
        }
    }
}

void dijkstra(double **matrix, int origem){
    int distancias[TAM]; 
    int visitados[TAM];
    int prev[TAM];

    for (int i = 0; i < TAM; i++) {
        distancias[i] = INF;
        visitados[i] = 0;
        prev[i] = -1;
    }

    distancias[origem] = 0;

    for (int count = 0; count < TAM - 1; count++) {
        int u = distanciaMin(distancias, visitados);

        visitados[u] = 1;

        for (int v = 0; v < TAM; v++) {
            if (!visitados[v] && matrix[u][v] > 0 && distancias[u] != INF && distancias[u] + matrix[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + matrix[u][v];
                prev[v] = u;
            }
        }
    }

    mostrarMenoresCaminhos(distancias, prev, origem);
}

void menu(double **matrix){
    int resp, cidadePartida;

    do{
        printf("=========================\n");
        printf("           MENU          \n");
        printf("=========================\n");
        printf("|[1] - Cadastrar estrada|\n");
        printf("|[2] - Ver estradas     |\n");
        printf("|[3] - Consultar estrada|\n");
        printf("|[4] - Excluir estrada  |\n");
        printf("|[5] - Menores caminhos |\n");
        printf("|[0] - Sair do sistema  |\n");
        printf("=========================\n");

        printf("Funcionalidade desejada: ");
        scanf("%d", &resp);

        while(resp < 0 || resp > 5){
            printf("Funcionalidade inexistente, tente novamente: ");
            scanf("%d", &resp);
        }

        switch (resp)
        {
        case 1:
            cadastrarEstrada(matrix);
            break;
        case 2:
            verEstradas(matrix);
            break;
        case 3:
            consultarEstrada(matrix);
            break;    
        case 4:
            excluirEstrada(matrix);
            break;    
        case 5:
            printf("Informe a cidade de partida: ");
            scanf("%d", &cidadePartida);

            while(cidadePartida < 0 || cidadePartida > TAM){
                printf("Esta cidade não existe, informe outra: ");
                scanf("%d", &cidadePartida);
            }

            dijkstra(matrix, cidadePartida);
        default:
            break;
        }

    }while(resp != 0);
      
}
