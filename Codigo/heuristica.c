#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arbol.h"
#include "juego.h"
#include "minimax.h"
#include "heuristica.h"

int puntuarArray(char v[4]) {
    int x = 0;
    int o = 0;
    int vuit = 0;

    for (int i = 0; i < 4; i++) {
        if (v[i] == 'x') x++;
        else if (v[i] == 'o') o++;
        else vuit++;
    }

    if (x == 4) return 1000000000;
    if (o == 4) return -1000000000;

    if (x > 0 && o > 0) return 0;

    if (x == 3 && vuit == 1) return 50000;
    if (x == 2 && vuit == 2) return 100;
    if (x == 1 && vuit == 3) return 10;

    if (o == 3 && vuit == 1) return -100000;
    if (o == 2 && vuit == 2) return -200;
    if (o == 1 && vuit == 3) return -20;

    return 0;
}

int heuristica(int N,int M, char tauler[][M]) {
    int puntuacio = 0;
    char array[4];
    int centre = M / 2;
    for (int i = 0; i < N; i++) {
        if (tauler[i][centre] == 'x') puntuacio += 5;
        else if (tauler[i][centre] == 'o') puntuacio -= 6;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= M - 4; j++) {
            for (int k = 0; k < 4; k++) {
                array[k] = tauler[i][j + k];
            }
            puntuacio += puntuarArray(array);
        }
    }
    for (int i = 0; i <= N - 4; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 4; k++) {
                array[k] = tauler[i + k][j];
            }
            puntuacio += puntuarArray(array);
        }
    }
    for (int i = 0; i <= N - 4; i++) {
        for (int j = 0; j <= M - 4; j++) {
            for (int k = 0; k < 4; k++) {
                array[k] = tauler[i + k][j + k];
            }
            puntuacio += puntuarArray(array);
        }
    }
    for (int i = 3; i < N; i++) {
        for (int j = 0; j <= M - 4; j++) {
            for (int k = 0; k < 4; k++) {
                array[k] = tauler[i - k][j + k];
            }
            puntuacio += puntuarArray(array);
        }
    }

    return puntuacio;
}
