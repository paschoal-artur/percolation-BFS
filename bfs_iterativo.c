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
void bfs(int *visitado, int *distancia, int L, int start) {
    int *fila = (int *)malloc(N * sizeof(int)); // Fila para BFS
    int inicio = 0, fim = 0; // Ponteiros da fila

    // Inicializa o nó inicial
    fila[fim++] = start;
    visitado[start] = 1;
    distancia[start] = 0;

    printf("Iniciando BFS padrão e cálculo de distâncias...\n");

    while (inicio < fim) {
        // Remove o primeiro elemento da fila
        int node = fila[inicio++];
        printf("Visitando nó %d\n", node);

        // Explora os vizinhos do nó atual
        for (int dir = 1; dir <= 4; dir++) {
            int viz = vizinho(node, dir, L);

            // Verifica se o vizinho é válido e ainda não foi visitado
            if (viz != -1 && !visitado[viz]) {
                fila[fim++] = viz; // Adiciona o vizinho à fila
                visitado[viz] = 1; // Marca como visitado
                distancia[viz] = distancia[node] + 1; // Calcula a distância
            }
        }
    }

    free(fila); // Libera a memória da fila
}

int contaNos(int *visitado, int L) {
    int cont = 0;
    for (int i = 0; i < L * L; i++) {
        if (visitado[i]) cont++;
    }
    return cont;
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

    // Alocar memória para os arrays de visitados e distâncias
    int *visitado = (int *)calloc(N, sizeof(int));
    int *distancia = (int *)malloc(N * sizeof(int));
    if (visitado == NULL || distancia == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Inicializa o array de distâncias com -1 (não visitado)
    for (int i = 0; i < N; i++) {
        distancia[i] = -1;
    }

    // Chama a BFS Iterativa a partir do nó inicial (0)
    bfs(visitado, distancia, L, 0);

    int totalVisitados = contaNos(visitado, L);
    printf("Total de nós visitados: %d\n", totalVisitados);

    //exibir a distancia para cada nó
    printf("\nDistâncias de cada nó a partir do nó inicial:\n");
    for (int i = 0; i < N; i++) {
        if (distancia[i] != -1) {
            printf("Nó %d: distância = %d\n", i, distancia[i]);
        } else {
            printf("Nó %d: não alcançável\n", i);
        }
    }

    // Libera memória alocada
    free(visitado);

    return 0;
}
