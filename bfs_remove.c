#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int N; // Número de nós na grade

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

// Função BFS Iterativa com remoção de nós
void bfs(bool *estado, int *contador, int L, int start) {
    int *fila = (int *)malloc(N * sizeof(int)); // Fila para BFS
    int inicio = 0, fim = 0; // Ponteiros da fila

    // Inicializa o nó inicial
    fila[fim++] = start;
    contador[start]++;

    printf("Iniciando BFS com remoção de nós...\n");

    while (inicio < fim) {
        // Remove o primeiro elemento da fila
        int node = fila[inicio++];
        printf("Visitando nó %d\n", node);

        // Explora os vizinhos do nó atual
        for (int dir = 1; dir <= 4; dir++) {
            int viz = vizinho(node, dir, L);

            // Verifica se o vizinho é válido e está ativo
            if (viz != -1 && estado[viz]) {
                contador[viz]++; // Incrementa o contador para o vizinho
                if (contador[node] == 2) {
                    // Se o nó atual foi visitado duas vezes, remove o último vizinho
                    estado[viz] = false;
                    printf("Nó %d foi visitado 2 vezes. Removendo o nó %d.\n", node, viz);
                    continue;
                }
                fila[fim++] = viz; // Adiciona o vizinho à fila
            }
        }
    }

    free(fila); // Libera a memória da fila
}

int main(int argc, char **argv) {
    int L; // Tamanho da grade

    // Verificar se o tamanho foi fornecido na linha de comando
    if (argc == 2) {
        L = atoi(argv[1]); // Converte o argumento da linha de comando para inteiro
    } else {
        // Caso contrário, solicita o tamanho da grade ao usuário
        printf("Digite o tamanho da grade (L): ");
        scanf("%d", &L);
    }

    if (L <= 0) {
        printf("O tamanho da grade deve ser maior que 0.\n");
        return 1;
    }

    N = L * L; // Total de nós na grade

    // Alocar memória para o estado dos nós e o contador de visitas
    bool *estado = (bool *)malloc(N * sizeof(bool));
    int *contador = (int *)calloc(N, sizeof(int));
    if (estado == NULL || contador == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Inicializa o estado de todos os nós como true (ativos)
    for (int i = 0; i < N; i++) {
        estado[i] = true;
    }

    // Solicitar o nó inicial
    int start;
    printf("Digite o nó inicial: ");
    scanf("%d", &start);

    // Validar o nó inicial
    if (start < 0 || start >= N) {
        printf("Erro: Nó inicial está fora dos limites.\n");
        free(estado);
        free(contador);
        return 1;
    }

    // Executa o BFS
    bfs(estado, contador, L, start);

    // Exibe o estado final dos nós
    printf("\nEstado final dos nós:\n");
    for (int i = 0; i < N; i++) {
        printf("Nó %d: %s\n", i, estado[i] ? "ativo" : "removido");
    }

    // Libera a memória alocada
    free(estado);
    free(contador);

    return 0;
}
