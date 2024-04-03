#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TAM 100
#define INF INT_MAX

double **criarMatrix();
void liberarMatrix(double **matrix);
void inicializarMatrix(double **matrix);
void mostrarMatrix(double **matrix);
void menu(double **matrix);
void cadastrarEstrada(double **matrix);
void verEstradas(double **matrix);
void consultarEstrada(double **matrix);
void excluirEstrada(double **matrix);
int distanciaMin(int distancias[], int visitados[]);
void mostrarCaminho(int prev[], int j);
void mostrarMenoresCaminhos(int distancias[], int prev[], int origem);
void dijkstra(double **matrix, int origem);