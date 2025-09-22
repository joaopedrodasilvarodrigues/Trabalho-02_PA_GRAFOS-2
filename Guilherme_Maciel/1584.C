#include <stdlib.h>
#include <stdio.h>
#define TAM 1000 
typedef struct {
    int custo, ponto;
} No;
typedef struct {
    int x, y;
} Ponto;
void heapify(No* heap, int tamanhoHeap, int i);
void inserirHeap(No** heap, int* tamanhoHeap, No no);
No removerMinHeap(No* heap, int* tamanhoHeap);
int distManhattan(Ponto p1, Ponto p2);
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    Ponto* pontos = (Ponto*)malloc(pointsSize * sizeof(Ponto));
    for (int i = 0; i < pointsSize; i++) {
        pontos[i].x = points[i][0];
        pontos[i].y = points[i][1];
    }
    int* visitado = (int*)malloc(pointsSize * sizeof(int));
    for (int i = 0; i < pointsSize; i++) visitado[i] = 0;
    int custoTotal = 0;
    int tamanhoHeap = 0;
    No* heap = (No*)malloc(TAM * sizeof(No));
    inserirHeap(&heap, &tamanhoHeap, (No){0, 0}); 
    while (tamanhoHeap > 0) {
        No no = removerMinHeap(heap, &tamanhoHeap);
        int pontoAtual = no.ponto;
        int custoAtual = no.custo;
        if (visitado[pontoAtual]) continue;
        visitado[pontoAtual] = 1;
        custoTotal += custoAtual;
        for (int i = 0; i < pointsSize; i++) {
            if (!visitado[i]) {
                int dist = distManhattan(pontos[pontoAtual], pontos[i]);
                inserirHeap(&heap, &tamanhoHeap, (No){dist, i});
            }
        }
    }
    return custoTotal;
}
int distManhattan(Ponto p1, Ponto p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
void heapify(No* heap, int tamanhoHeap, int i) {
    int menor = i;
    int esquerda = 2 * i +*
