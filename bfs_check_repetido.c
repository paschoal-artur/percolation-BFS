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

// Função BFS Iterativa para detectar visitas múltiplas
int* bfs(int *contador, int L, int start, int *tamanhoFila) {
    int *fila = (int *)malloc(N * sizeof(int)); // Fila para BFS
    int inicio = 0, fim = 0; // Ponteiros da fila

    // Inicializa o nó inicial
    fila[fim++] = start;
    contador[start]++;

    printf("Iniciando BFS a partir do nó %d e monitorando visitas duplicadas...\n", start);

    while (inicio < fim) {
        // Remove o primeiro elemento da fila
        int node = fila[inicio++];
        printf("Visitando nó %d\n", node);

        // Explora os vizinhos do nó atual
        for (int dir = 1; dir <= 4; dir++) {
            int viz = vizinho(node, dir, L);

            // Verifica se o vizinho é válido
            if (viz != -1) {
                contador[viz]++; // Incrementa o contador para o vizinho
                if (contador[viz] == 2) {
                    // Retorna a fila ao detectar a segunda visita
                    printf("\nNó %d foi visitado pela segunda vez. Retornando a fila...\n", viz);
                    *tamanhoFila = fim;
                    return fila;
                }
                fila[fim++] = viz; // Adiciona o vizinho à fila
            }
        }
    }

    *tamanhoFila = fim; // Retorna o tamanho final da fila
    return fila; // Retorna a fila ao final do BFS
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

    // Alocar memória para o contador de visitas
    int *contador = (int *)calloc(N, sizeof(int));
    if (contador == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Solicitar o nó inicial
    int start;
    printf("Digite o nó inicial: ");
    scanf("%d", &start);

    // Validar o nó inicial
    if (start < 0 || start >= N) {
        printf("Erro: Nó inicial está fora dos limites.\n");
        free(contador);
        return 1;
    }

    // Executa o BFS
    int tamanhoFila = 0;
    int *fila = bfs(contador, L, start, &tamanhoFila);

    // Exibe os elementos da fila retornada
    printf("\nFila retornada:\n");
    for (int i = 0; i < tamanhoFila; i++) {
        printf("%d ", fila[i]);
    }
    printf("\n");

    // Libera a memória alocada
    free(contador);
    free(fila);

    return 0;
}
