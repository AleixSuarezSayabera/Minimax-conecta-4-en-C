#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "arbol.h"
#include "juego.h"
#include "minimax.h"
#include "heuristica.h"


int MinMax(Node *arrel, int nivell, int alpha, int beta) {
    if (arrel->n_fills == 0) {
        return arrel->valor;
    }
    if (nivell % 2 == 0) {
        int mejor = INT_MIN;
        for (int i = 0; i < arrel->n_fills; i++) {
            int valorHijo = MinMax(arrel->fills[i], nivell + 1, alpha, beta);
            if (valorHijo > mejor) {
                mejor = valorHijo;
            }
            if (valorHijo > alpha) {
                alpha = mejor;
            }
            if (beta <= alpha) break;
        }
        arrel->valor = mejor;
        return mejor;
    }
    else {
        int peor = INT_MAX;
        for (int i = 0; i < arrel->n_fills; i++) {
            int valorHijo = MinMax(arrel->fills[i], nivell + 1, alpha, beta);
            if (valorHijo < peor) {
                peor = valorHijo;
            }
            if (valorHijo < beta) {
                beta = peor;
            }
            if (beta <= alpha) break;
        }
        arrel->valor = peor;
        return peor;
    }
}

int Ordinador(int N, int M, char tauler[N][M], int top[M], int NIVELL) {
    Node *arrel = malloc(sizeof(Node));
    arrel->top = malloc(M * sizeof(int));
    CopiarTop(M,top, arrel->top);
    arrel->n_fills = calculaNumFills(arrel->top,M,N);
    arrel->fills = malloc(arrel->n_fills * sizeof(Node*));
    arrel->pare=NULL;
    crearArbre(arrel, N,M,tauler,NIVELL);
    MinMax(arrel, 0, INT_MIN, INT_MAX);
    int mejorValor = INT_MIN;
    int mejorColumna = -1;
    for (int i = 0; i < arrel->n_fills; i++) {
        if (arrel->fills[i]->valor > mejorValor) {
            mejorValor = arrel->fills[i]->valor;
            mejorColumna = arrel->fills[i]->columna;
        }
    }
    printf("La IA ha triat la columna %i\n", mejorColumna + 1);
    printf("El valor d'aquesta jugada ha sigut %i\n",mejorValor);
    //recorrerArbol(arrel,0);
    liberar(arrel);
    return mejorColumna;
}
