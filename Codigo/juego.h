#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

void Banner();

int benvinguda(int *N,int *M, int *NIVELL);

void configuracio(int *N, int *M, int *NIVELL);

void canviTauler(int *N, int *M);

void canviDificultat(int *NIVELL);

int JugarPartidaNova(int N, int M, int NIVELL);

void PartidaHumans(int N,int M);

void PartidaIA(int N, int M,int NIVELL);

bool TaulerPle(int top[],int M, int N);

int PreguntarPorColumna(int N,int M, char tauler[N][M], int top[M], int torn);

void gravedad1(int N,int M,char tauler[N][M],int top[M], int i);

void gravedad2(int N, int M, char tauler[][M],int top[], int i);

void inicializar(int top[], int M);

bool GanarPorDiagCrec(int N, int M, char tauler[][M], int top[], int i);

bool GanarPorFila(int N, int M, char tauler[][M], int top[], int i);

bool GanarPorDiagDecrec(int N, int M, char tauler[][M], int top[], int i);

bool GanarPorColumna(int N, int M, char tauler[][M], int top[], int i);

bool Victoria(int N, int M, char tauler[][M], int top[], int i);

void ImprimirTablero(int N, int M, char t[][M]);

void OmplirDeZeros(int N,int M, char tauler[][M]);

int pilaPlena(int top[], int i, int N,int M);
