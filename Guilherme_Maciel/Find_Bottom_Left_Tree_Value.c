#include <stdlib.h>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct {
    struct TreeNode* node;
    int nivel;
} listaFila;

typedef struct {
    listaFila* dados;
    int tras, frente, tam, capacidade;
} Fila;

Fila* criarFila(int capacidade);
int vazia(Fila* f);
void enfileirar(Fila* f, struct TreeNode* node, int nivel);
listaFila desenfileirar(Fila* f);

int findBottomLeftValue(struct TreeNode* root) {
    Fila* f = criarFila(10000); 
    enfileirar(f, root, 0);
    int noEsquerdo = root->val;
    int nivelAtual = 0;
    while (!vazia(f)) {
        listaFila item = desenfileirar(f);
        struct TreeNode* node = item.node;
        int nivel = item.nivel;
        if (node->left) enfileirar(f, node->left, nivel +1);
        if (node->right) enfileirar(f, node->right, nivel +1);
        if (nivel > nivelAtual) {
            noEsquerdo = node->val;
            nivelAtual = nivel;
        }
    }
    return noEsquerdo;
}

Fila* criarFila(int capacidade) {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->dados = (listaFila*)malloc(sizeof(listaFila) * capacidade);
    f->frente = 0;
    f->tras = -1;
    f->tam = 0;
    f->capacidade = capacidade;
    return f;
}

int vazia(Fila* f) {
    return f->tam == 0;
}

void enfileirar(Fila* f, struct TreeNode* node, int nivel) {
    if (f->tam == f->capacidade) return;
    f->tras = (f->tras + 1) % f->capacidade;
    f->dados[f->tras].node = node;
    f->dados[f->tras].nivel = nivel;
    f->tam++;
}

listaFila desenfileirar(Fila* f) {
    listaFila item = f->dados[f->frente];
    f->frente = (f->frente + 1) % f->capacidade;
    f->tam--;
    return item;
}
