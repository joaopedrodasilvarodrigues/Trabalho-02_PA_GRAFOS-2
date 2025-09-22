#include <stdlib.h>
typedef struct { int x, y, h; 
}Celula;
int compara(const void *a, const void *b) { 
    return ((Celula*)a)->h - ((Celula*)b)->h;
}
int unionFind(int *raiz, int x) { 
    if (raiz[x] == x) return x; 
    else {
      raiz[x] = unionFind(raiz, raiz[x]); return raiz[x]; 
        }
}
void uniao(int *raiz, int a, int b){  
    a = unionFind(raiz, a); b = unionFind(raiz, b); 
    if (a == b) return; 
    raiz[a] = b;
}

int swimInWater(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize, N = n * n;
    Celula *celulas = malloc(N * sizeof(Celula)); 
    int k = 0;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            celulas[k++] = (Celula){i, j, grid[i][j]};
    qsort(celulas, N, sizeof(Celula), compara);
    int *raiz = malloc(N * sizeof(int)); 
    for (int i = 0; i < N; i++) raiz[i] = i;
    int direcoes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 
    int submersso[n][n]; 
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            submersso[i][j] = 0;
    for (int i = 0; i < N; i++) {
        int x = celulas[i].x, y = celulas[i].y, h = celulas[i].h;
        submersso[x][y] = 1; 
        int id = x * n + y;
        for (int d = 0; d < 4; d++) { 
            int nx = x + direcoes[d][0], ny = y + direcoes[d][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && submersso[nx][ny]) 
                uniao(raiz, id, nx * n + ny); 
        }
        if (unionFind(raiz, 0) == unionFind(raiz, N - 1)) 
            return h; 
    }
    return -1; 
}
