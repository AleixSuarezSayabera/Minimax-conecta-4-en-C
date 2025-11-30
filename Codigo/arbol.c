#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arbol.h"
#include "juego.h"
#include "minimax.h"
#include "heuristica.h"


int calculaNumFills(int top[],int M,int N){
    int posibilitats=0;
    for(int i=0;i<M;i++){
        if(!pilaPlena(top,i,N,M)){
            posibilitats++;
        }
    }
    return posibilitats;
    }

void recrearTauler(int N, int M, char tauler[N][M], char taulerfinal[N][M], Node *fulla){
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            taulerfinal[i][j] = tauler[i][j];

    int moviments[N*M];
    int n = 0;
    Node *p = fulla;

    while (p->pare != NULL) {
        moviments[n++] = p->columna;
        p = p->pare;
    }


    int topLocal[M];
    for (int i = 0; i < M; i++) topLocal[i] = p->top[i];


    int turno = 0;

    for (int k = n - 1; k >= 0; k--) {
        int col = moviments[k];
        int fila = ++topLocal[col];
        if(turno%2==0){
            taulerfinal[fila][col]='x';
        }
        if(turno%2==1){
            taulerfinal[fila][col]='o';
        }
        turno++;
    }
}

Node* creaNode(int N, int M, int NIVELL, Node *pare,int columna,int nivell,char tauler[N][M]) {
	Node *p=malloc(sizeof(Node));
	p->top = malloc(M * sizeof(int));
	CopiarTop(M,pare->top,p->top);
	p->top[columna]++;
	p->columna=columna;
    p->pare=pare;
	if (nivell < NIVELL - 1) {
        int nfills = calculaNumFills(p->top,M,N);
        if (nfills == 0) {
            char taulerfinal[N][M];
            recrearTauler(N,M,tauler, taulerfinal, p);
            //ImprimirTablero(N,M, taulerfinal);
            p->valor = heuristica(N,M,taulerfinal);
            //printf("valor del tauler %i\n", p->valor);
            p->n_fills = 0;
            p->fills = NULL;
        } else {
            p->valor = 0;
            p->n_fills = nfills;
            p->fills = malloc(p->n_fills * sizeof(Node *));
            if (!p->fills) { perror("malloc fills"); exit(EXIT_FAILURE); }
            for (int k = 0; k < p->n_fills; ++k) p->fills[k] = NULL;
        }
    }

    else {
        char taulerfinal[N][M];
        recrearTauler(N,M,tauler, taulerfinal, p);
        //ImprimirTablero(N,M,taulerfinal);
        p->valor = heuristica(N,M,taulerfinal);
        //printf("valor del tauler %i\n", p->valor);
        p->n_fills = 0;
        p->fills = NULL;
    }
    return p;
}

int buscar(int M, int N, Node *pare, int j) {
    for (; j < M; j++)
        if (!pilaPlena(pare->top, j,N,M))
            return j;
    return -1;
}

void creaNivell(int N, int M, int NIVELL, Node *pare, int nivell,char tauler[N][M]) {
    if (pare == NULL) return;
    if (nivell >= NIVELL) return;
    if (pare->n_fills == 0) return;

    int idx = 0;
    for (int col = 0; col < M && idx < pare->n_fills; ++col) {
        if (!pilaPlena(pare->top, col,N,M)) {
            pare->fills[idx] = creaNode(N,M,NIVELL,pare, col, nivell,tauler);
            creaNivell(N,M,NIVELL,pare->fills[idx], nivell + 1,tauler);
            idx++;
        }
    }
    for (; idx < pare->n_fills; ++idx) pare->fills[idx] = NULL;
}

void crearArbre(Node *arrel,int N,int M, char tauler[N][M],int NIVELL) {
	creaNivell(N,M,NIVELL,arrel,0,tauler);
}



void recorrerArbol(Node *nodo, int nivel) {
    if (nodo == NULL) return;
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("Nivel %d | Valor: %d | N hijos: %d N columna: %d\n", nivel, nodo->valor, nodo->n_fills, nodo->columna);
    printf("\n");
    for (int i = 0; i < nodo->n_fills; i++) {
        recorrerArbol(nodo->fills[i], nivel + 1);
    }
}

void CopiarTop(int M, int topPare[M], int topFill[M]) {
    memcpy(topFill, topPare, M * sizeof(int));
}

void liberar(Node *arrel) {
    if (arrel == NULL) return;
    for (int i = 0; i < arrel->n_fills; i++) {
        liberar(arrel->fills[i]);
    }
    if (arrel->fills != NULL) {
        free(arrel->fills);
    }
    free(arrel);
}


