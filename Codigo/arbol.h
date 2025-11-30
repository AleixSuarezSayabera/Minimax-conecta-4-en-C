#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node {
    struct node **fills;
    struct node *pare;
    int n_fills;
    int *top;
    int valor;
    int columna;
    int nivell;
} Node;

int calculaNumFills(int top[],int M,int N);

void recrearTauler(int N, int M, char tauler[N][M], char taulerfinal[N][M], Node *fulla);

Node* creaNode(int N, int M, int NIVELL, Node *pare,int columna,int nivell,char tauler[N][M]);

int buscar(int M, int N, Node *pare, int j);

void creaNivell(int N, int M, int NIVELL, Node *pare, int nivell,char tauler[N][M]);

void crearArbre(Node *arrel,int N,int M, char tauler[N][M],int NIVELL);

void recorrerArbol(Node *nodo, int nivel);

void CopiarTop(int M, int topPare[M], int topFill[M]);

void liberar(Node *arrel);

