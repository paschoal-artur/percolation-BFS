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

// Função BFS recursiva, função com um calculador de distâncias
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

int contaNos(int *visitado, int L) {
    int cont = 0;
    for (int i = 0; i < L * L; i++) {
        if (visitado[i]) cont++;
    }
    return cont;
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

    // Alocar memória para o array de visitados
    int *visitado = (int *)calloc(N, sizeof(int));
    if (visitado == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Chamar BFS a partir do nó 0
    printf("Iniciando BFS...\n");
    bfs(visitado, 0, L);
    // Contar o número de nós visitados
    int totalVisitados = contaNos(visitado, L);
    printf("Número total de nós visitados: %d\n", totalVisitados);
    // Liberar a memória alocada
    free(visitado);
    return 0;
}
