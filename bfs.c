#include <stdio.h>
#include <stdlib.h>

int N; // número de nós

// Funções coordenadas
int X(int i, int L) {
    return i % L;
}

int Y(int i, int L) {
    return i / L;
}

// Função que retorna o vizinho de x na direção y
int vizinho(int x, int y, int L) {
    switch (y) {
        case 1: // cima
            if (x / L != L - 1) return x + L;
            else return -1;
        case 2: // baixo
            if (x >= L) return x - L;
            else return -1;
        case 3: // direita
            if ((x + 1) % L != 0) return x + 1;
            else return -1;
        case 4: // esquerda
            if (x % L != 0) return x - 1;
            else return -1;
    }
    return -1;
}

// Função BFS recursiva
void bfs(int *visitado, int node, int L) {
    // Marcar o vértice como visitado
    visitado[node] = 1;
    printf("Visitando nó %d\n", node);

    // Explorar os vizinhos do nó atual
    for (int dir = 1; dir <= 4; dir++) {
        int viz = vizinho(node, dir, L);
        if (viz != -1 && !visitado[viz]) {
            bfs(visitado, viz, L); // Chamada recursiva
        }
    }
}

int main(int argc, char **argv) {
    // Verificar se o número de argumentos está correto
    if (argc != 2) {
        printf("Uso: %s <tamanho da grade>\n", argv[0]);
        return 1;
    }

    // Obter o tamanho da grade
    int L = atoi(argv[1]); // lado da grade
    N = L * L; // número total de vértices

    // Alocar memória para o array de visitados
    int *visitado = (int *)calloc(N, sizeof(int));
    if (visitado == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Chamar BFS a partir do nó 0
    printf("Iniciando BFS...\n");
    bfs(visitado, 0, L);

    // Liberar a memória alocada
    free(visitado);
    return 0;
}
