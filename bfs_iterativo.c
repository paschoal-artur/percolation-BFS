#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

int N; // Número de nós na grade

// Funções coordenadas
int X(int i, int L) {
    return i % L;
}

int Y(int i, int L) {
    return i / L;
}

// Função para obter o vizinho de x na direção y
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

// Função BFS Iterativa
void bfs(int *visitado, int L, int start) {
    int *fila = (int *)malloc(N * sizeof(int)); // Fila para BFS
    int inicio = 0, fim = 0; // Ponteiros da fila

    // Adiciona o nó inicial à fila e marca como visitado
    fila[fim++] = start;
    visitado[start] = 1;

    printf("Iniciando BFS Iterativo...\n");

    while (inicio < fim) {
        // Remove o primeiro elemento da fila
        int node = fila[inicio++];
        printf("Visitando nó %d\n", node);

        // Explora os vizinhos do nó atual
        for (int dir = 1; dir <= 4; dir++) {
            int viz = vizinho(node, dir, L);

            // Verifica se o vizinho é válido e não foi visitado
            if (viz != -1 && !visitado[viz]) {
                fila[fim++] = viz; // Adiciona o vizinho à fila
                visitado[viz] = 1; // Marca como visitado
            }
        }
    }

    free(fila); // Libera a memória da fila
}

int main(int argc, char **argv) {
    int L;

    // Verifica se o tamanho foi fornecido na linha de comando
    if (argc == 2) {
        L = atoi(argv[1]);
    } else {
        printf("Digite o tamanho da grade (L): ");
        scanf("%d", &L);
    }

    if (L <= 0) {
        printf("O tamanho da grade deve ser maior que 0.\n");
        return 1;
    }

    N = L * L; // Total de nós na grade

    // Aloca memória para o array de visitados
    int *visitado = (int *)calloc(N, sizeof(int));
    if (visitado == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Chama a BFS Iterativa a partir do nó inicial (0)
    bfs(visitado, L, 0);

    // Libera memória alocada
    free(visitado);

    return 0;
}
