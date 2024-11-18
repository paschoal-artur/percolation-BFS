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

// Função BFS Iterativa com vetor binário de análise e cálculo de distância
int* bfs(int *visitado, int *ativo, int *distancia, int L, int start) {
    int *fila = (int *)malloc(N * sizeof(int)); // Fila para BFS
    int inicio = 0, fim = 0; // Ponteiros da fila

    int *analisados = (int *)calloc(N, sizeof(int)); // Vetor para armazenar nós analisados
    if (analisados == NULL) {
        perror("Erro ao alocar memória");
        free(fila);
        return NULL;
    }

    // Inicializa o nó inicial apenas se ele for ativo
    if (ativo[start]) {
        fila[fim++] = start;
        visitado[start] = 1;
        distancia[start] = 0; // Distância inicial
        analisados[start] = 1; // Marca como analisado
    }

    printf("Iniciando BFS com vetor de análise e cálculo de distâncias...\n");

    while (inicio < fim) {
        // Remove o primeiro elemento da fila
        int node = fila[inicio++];
        printf("Visitando nó %d com distância %d\n", node, distancia[node]);

        // Explora os vizinhos do nó atual
        for (int dir = 1; dir <= 4; dir++) {
            int viz = vizinho(node, dir, L);

            // Verifica se o vizinho é válido, ativo e ainda não foi visitado
            if (viz != -1 && ativo[viz] && !visitado[viz]) {
                fila[fim++] = viz; // Adiciona o vizinho à fila
                visitado[viz] = 1; // Marca como visitado
                analisados[viz] = 1; // Marca como analisado
                distancia[viz] = distancia[node] + 1; // Calcula a distância
            }
        }
    }

    free(fila); // Libera a memória da fila
    return analisados; // Retorna o vetor de nós analisados
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

    // Alocar memória para os arrays de visitados, ativos e distâncias
    int *visitado = (int *)calloc(N, sizeof(int));
    int *ativo = (int *)malloc(N * sizeof(int));
    int *distancia = (int *)malloc(N * sizeof(int));
    if (visitado == NULL || ativo == NULL || distancia == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Inicializa o vetor de ativos com valores 0 ou 1
    printf("Inicializando vetor de ativos (0 ou 1 para cada nó):\n");
    for (int i = 0; i < N; i++) {
        ativo[i] = rand() % 2; // Gera valores aleatórios (0 ou 1)
        printf("Nó %d: ativo = %d\n", i, ativo[i]);
    }

    // Inicializa o vetor de distâncias com -1 (não visitado)
    for (int i = 0; i < N; i++) {
        distancia[i] = -1;
    }

    // Executa o BFS
    int *analisados = bfs(visitado, ativo, distancia, L, 0);
    if (analisados == NULL) {
        free(visitado);
        free(ativo);
        free(distancia);
        return 1;
    }

    // Exibe os nós analisados
    printf("\nNós analisados:\n");
    for (int i = 0; i < N; i++) {
        if (analisados[i]) {
            printf("Nó %d foi analisado.\n", i);
        }
    }

    // Exibe as distâncias para cada nó
    printf("\nDistâncias de cada nó a partir do nó inicial:\n");
    for (int i = 0; i < N; i++) {
        if (distancia[i] != -1) {
            printf("Nó %d: distância = %d\n", i, distancia[i]);
        } else {
            printf("Nó %d: não alcançável\n", i);
        }
    }

    // Libera a memória alocada
    free(visitado);
    free(ativo);
    free(distancia);
    free(analisados);

    return 0;
}
