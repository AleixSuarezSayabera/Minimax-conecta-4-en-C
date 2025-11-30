#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "arbol.h"
#include "juego.h"
#include "minimax.h"
#include "heuristica.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Banner() {
    clearScreen();
    printf(
    "*******************************\n"
    "*         4 EN RATLLA         *\n"
    "*      Benvingut al joc!      *\n"
    "*******************************\n"
    );
}

int benvinguda(int *N,int *M, int *NIVELL) {
    while (1) {
        Banner();
        int j;
        printf("\nQue vols fer?\n"
               "  1. Jugar una partida nova\n"
               "  2. Configuracio\n"
               "  3. Indicacions\n"
               "  4. Sortir del joc\n"
               "Opcio = ");

        if (scanf("%d", &j) != 1) {
            printf("Has d'introduir un enter valid!\n");
            while (getchar() != '\n');
            continue;
        }

        if (j == 1) {
            JugarPartidaNova(*N,*M,*NIVELL);
        }
        else if (j == 2) {
            configuracio(N,M,NIVELL);
        }
        else if (j == 3) {
            instruccions();
        }
        else if (j == 4) {
            printf("Sortint...\n");
            return 0;
        }
        else {
            printf("Opcio no valida.\n");
        }
    }
}

void instruccions(){
    clearScreen();
    printf("Instruccions del meu 4 en ratlla:\n\n"
           "- Es juga com el classic Connecta4, no hi han normes canviades.\n"
           "- Pots modificar la mida del tauler i la dificultat a Configuracio.\n"
           "- Per defecte: tauler 6x7 i IA amb dificultat mitjana (nivell 4 de profunditat al minimax).\n"
           "- Modes de joc: huma VS huma o contra la IA.\n"
           "- Les 'o' sempre comencen. La IA sempre juga amb 'x' sigui el torn que sigui.\n\n");
    printf("Prem Enter per tornar al menu.");
    while (getchar() != '\n');
    getchar();
}

void configuracio(int *N, int *M, int *NIVELL){
    clearScreen();
    int i;
    printf("Configuracio del joc\n\n"
           "  1. Canviar mida del tauler\n"
           "  2. Canviar dificultat\n"
           "  3. Tornar al menu\n"
           "Opcio = ");

    if (scanf("%d", &i) != 1) {
        printf("Has d'introduir un numero valid!\n");
        while (getchar() != '\n');
        return;
    }

    if (i == 1) {
        canviTauler(N, M);
    }
    else if (i == 2) {
        canviDificultat(NIVELL);
    }
    else if (i == 3) {
        return;
    }
    else {
        printf("Opcio no valida\n");
    }
}

void canviTauler(int *N, int *M){
    clearScreen();
    printf("Actualment el tauler es de mida %dx%d\n", *N, *M);
    printf("Introdueix el nou valor de N: ");
    scanf("%d", N);
    printf("Introdueix el nou valor de M: ");
    scanf("%d", M);

    printf("Ara el tauler es de mida %dx%d\n", *N, *M);
    printf("Prem Enter per tornar\n");
    while (getchar() != '\n');
    getchar();
}

void canviDificultat(int *NIVELL){
    clearScreen();
    int i;

    printf("Selecciona dificultat:\n"
           "  1. Facil\n"
           "  2. Normal\n"
           "  3. Mitjana\n"
           "  4. Dificil\n"
           "  5. Molt dificil (trigara bastant...)\n"
           "  6. Cancel.lar\n"
           "Opcio = ");

    if (scanf("%d", &i) != 1) {
        printf("Has d'introduir un numero valid!\n");
        while (getchar() != '\n');
        return;
    }

    if (i == 1) {
        *NIVELL = 1;
        printf("Ara la IA jugara amb dificultat: Facil\n");
    }
    else if (i == 2) {
        *NIVELL = 2;
        printf("Ara la IA jugara amb dificultat: Normal\n");
    }
    else if (i == 3) {
        *NIVELL = 4;
        printf("Ara la IA jugara amb dificultat: Mitjana\n");
    }
    else if (i == 4) {
        *NIVELL = 6;
        printf("Ara la IA jugara amb dificultat: Dificil\n");
    }
    else if (i == 5) {
        *NIVELL = 8;
        printf("Ara la IA jugara amb dificultat: Molt dificil\n");
    }
    else if (i == 6) {
        return;
    }
    else {
        printf("Opcio no valida\n");
        return;
    }

    printf("Prem Enter per tornar\n");
    while (getchar() != '\n');
    getchar();
}
int JugarPartidaNova(int N, int M, int NIVELL) {
    clearScreen();
    int i;

    while (1) {
        printf("Modes de joc:\n"
               "  1. Partida local (huma VS huma)\n"
               "  2. Contra l'ordinador\n"
               "  3. Tornar al menu\n"
               "Opcio = ");

        if (scanf("%d", &i) != 1) {
            printf("Has d'introduir un numero valid!\n");
            while (getchar() != '\n');
            continue;
        }

        if (i == 1) {
            PartidaHumans(N,M);
            return 1;
        }
        else if (i == 2) {
            PartidaIA(N,M,NIVELL);
            return 1;
        }
        else if (i == 3) {
            return 1;
        }
        else {
            printf("Opcio no valida.\n");
        }
    }
}

void PartidaHumans(int N,int M) {
    clearScreen();
    char tauler[N][M];
    int top[M];

    inicializar(top,M);
    OmplirDeZeros(N,M,tauler);
    printf("Comenca el jugador 1: 'o'\n");
    int torn = 0;

    while (!TaulerPle(top,M,N)) {
        int j = PreguntarPorColumna(N,M,tauler, top, torn);

        if (Victoria(N,M,tauler, top, j)) {
            if (torn % 2 == 0){
                printf("Ha guanyat el jugador 1!!!\n");
            } else {
                printf("Ha guanyat el jugador 2!!!\n");
            }
            printf("Prem Enter per tornar al menu.");
            while (getchar() != '\n');
            getchar();
            return;
        }
        torn++;
    }

    printf("Heu quedat empat!\n");
    printf("Prem Enter per tornar al menu.");
    while (getchar() != '\n');
    getchar();
}

void PartidaIA(int N, int M,int NIVELL) {
    clearScreen();
    char tauler[N][M];
    int top[M];
    inicializar(top,M);
    OmplirDeZeros(N,M,tauler);
    int l = 0, torn = 0;

    while (1) {
        printf("Qui comenca?\n"
               "  1. Huma\n"
               "  2. IA\n"
               "  3. Aleatori\n"
               "Opcio = ");
        if (scanf("%d", &l) != 1) {
            printf("Has d'introduir un 1, 2 o 3\n");
            while (getchar() != '\n');
            continue;
        }
        if (l >= 1 && l <= 3) break;
        printf("Opcio no valida.\n");
    }

    if (l == 1) {
        torn = 0;
        clearScreen();
        printf("Comences tu... preparat!\n");
    }
    else if (l == 2) {
        torn = 1;
        clearScreen();
        printf("Comenca la IA... preparat!\n");
    }
    else {
        srand(time(NULL));
        torn = rand() % 2;
        clearScreen();
        if(torn==0){
           printf("L'atzar ha decidit que comences tu... preparat!\n");
        }
        else {
           printf("L'atzar ha decidit que comenca la IA!\n");
        }
    }

    while (!TaulerPle(top,M,N)) {
        if (torn % 2 == 0) {
            int j = PreguntarPorColumna(N,M,tauler, top,torn);
            if (Victoria(N,M,tauler, top, j)) {
                printf("Has guanyat!!!\n");
                printf("Prem Enter per tornar al menu.");
                while (getchar() != '\n');
                getchar();
                return;
            }
        } else {
            clearScreen();
            int j = Ordinador(N,M,tauler, top, NIVELL);
            gravedad2(N,M,tauler, top, j);
            ImprimirTablero(N,M,tauler);
            if (Victoria(N,M,tauler, top, j)) {
                printf("La IA ha guanyat!\n");
                printf("Prem Enter per tornar al menu.");
                while (getchar() != '\n');
                getchar();
                return;
            }
        }
        torn++;
    }

    printf("Has conseguit empatar, enhorabona!\n");
    printf("Prem Enter per tornar al menu.");
    while (getchar() != '\n');
    getchar();
}

bool TaulerPle(int top[],int M, int N){
    int i=0;
    for(int j=0;j<M;j++){
    i = i+top[j];
    }
    if (i>=(N-1)*(M)){
        return true;
    }
    else return false;
}

int PreguntarPorColumna(int N,int M, char tauler[N][M], int top[M], int torn) {
    int i;
    while (1) {
        if (torn % 2 == 0){
            printf("Jugador 1, columna (1-%d): ", M);
        }
        else {
            printf("Jugador 2, columna (1-%d): ", M);
        }
        if (scanf("%d", &i) != 1) {
            printf("Has d'introduir una columna valida!\n");
            while (getchar() != '\n');
            continue;
        }
        i--;
        if (i < 0 || i >= M) {
            printf("Columna no valida.\n");
            continue;
        }
        if (pilaPlena(top, i, N, M)) {
            printf("Columna plena.\n");
            continue;
        }
        clearScreen();
        if (torn % 2 == 0){
            gravedad1(N, M, tauler, top, i);
        }
        else {
            gravedad2(N, M, tauler, top, i);
        }
        ImprimirTablero(N,M,tauler);
        return i;
    }
}

void gravedad1(int N,int M,char tauler[N][M],int top[M], int i){
    if (!pilaPlena(top,i,N,M)) {
        tauler[++top[i]][i]='o';
    }
}

void gravedad2(int N, int M, char tauler[][M],int top[], int i){
    if (!pilaPlena(top,i,N,M)) {
        tauler[++top[i]][i]='x';
    }
}

void inicializar(int top[], int M){
    for(int k=0;k<M;k++){
        top[k]=-1;
    }
}

bool GanarPorDiagCrec(int N, int M, char tauler[][M], int top[], int i){
    int fila = top[i];
    char p = tauler[fila][i];
    if (p == ' ') {
        return false;
    }
    for (int f = fila - 3; f <= fila; f++) {
        int c = i - (fila - f);

        if (f < 0 || f + 3 >= N) {
            continue;
        }
        if (c < 0 || c + 3 >= M) {
            continue;
        }
        if (tauler[f][c] == p &&
            tauler[f+1][c+1] == p &&
            tauler[f+2][c+2] == p &&
            tauler[f+3][c+3] == p){
            return true;
        }
    }
    return false;
}

bool GanarPorFila(int N, int M, char tauler[][M], int top[], int i){
    for (int j=0; j<= M - 4; j++) {
        if (tauler[top[i]][j] != ' ' &&
            tauler[top[i]][j+1] == tauler[top[i]][j] &&
            tauler[top[i]][j+2] == tauler[top[i]][j] &&
            tauler[top[i]][j+3] == tauler[top[i]][j]) {
            return true;
        }
    }
    return false;
}

bool GanarPorDiagDecrec(int N, int M, char tauler[][M], int top[], int i){
    int fila = top[i];
    char p = tauler[fila][i];
    if (p == ' ') return false;
    for (int f = fila - 3; f <= fila; f++) {
        int c = i + (fila - f);
        if (f < 0 || f + 3 >= N) {
            continue;
        }
        if (c - 3 < 0 || c >= M) {
            continue;
        }

        if (tauler[f][c] == p &&
            tauler[f+1][c-1] == p &&
            tauler[f+2][c-2] == p &&
            tauler[f+3][c-3] == p){
            return true;
            }
    }
    return false;
}

bool GanarPorColumna(int N, int M, char tauler[][M], int top[], int i){
    if(top[i]>2){
        if(tauler[top[i]][i] != ' ' &&
           tauler[top[i]-1][i]==tauler[top[i]][i] &&
           tauler[top[i]-2][i]==tauler[top[i]][i] &&
           tauler[top[i]-3][i]==tauler[top[i]][i]){
            return true;
        }
    }
    return false;
}



bool Victoria(int N, int M, char tauler[][M], int top[], int i){
    if(GanarPorColumna(N,M,tauler,top,i)  ||
       GanarPorFila(N,M,tauler,top,i)     ||
       GanarPorDiagCrec(N,M,tauler,top,i) ||
       GanarPorDiagDecrec(N,M,tauler,top,i)){
        return true;
       }
    return false;
}

void ImprimirTablero(int N, int M, char t[][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("+---");
        printf("+\n");

        for (int j = 0; j < M; j++)
            printf("| %c ", t[N - 1 - i][j]);
        printf("|\n");
    }
    for (int j = 0; j < M; j++)
        printf("+---");
    printf("+\n");
    for (int j = 0; j < M; j++)
        printf("  %d ", j + 1);
    printf("\n");
}

void OmplirDeZeros(int N,int M, char tauler[][M]){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            tauler[i][j]=' ';
        }
    }
}

int pilaPlena(int top[], int i, int N,int M) {
    if (i < 0 || i >= M) return 1;
    return top[i] >= N - 1;
}
