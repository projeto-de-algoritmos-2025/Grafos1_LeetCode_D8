//O objetivo é encontrar a sequência de células adjacentes 
//onde cada célula tem um valor maior que a anterior, 
//e essa sequência seja a mais longa possível.

#include <stdio.h>
#include <stdlib.h>

// Matriz para memoização que armazena o comprimento do caminho crescente mais longo a partir de cada célula
int **memo;

// Direções possíveis dx e dy para baixo, cima, direita e esquerda
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

// Dimensões da matriz
int rows, cols; // linhas e colunas 

// Função DFS com memoização para calcular o caminho crescente mais longo a partir de (r, c)
int dfs(int **matrix, int r, int c) {

    if (memo[r][c] != 0) {
        return memo[r][c];
    } // Se o resultado para esta célula já foi calculado, retorna-o

    // Inicializa o comprimento máximo a partir desta célula como 1 (a própria célula)
    int maxLen = 1;

    // Explora os 4 vizinhos (baixo, cima, direita, esquerda)
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i]; // Nova linha
        int nc = c + dy[i]; // Nova coluna

        // Verifica se o vizinho está dentro dos limites da matriz
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            // Se o valor do vizinho for maior que o valor da célula atual,
            // podemos estender o caminho crescente
            if (matrix[nr][nc] > matrix[r][c]) {
                // Calcula o comprimento do caminho através deste vizinho
                // e atualiza maxLen se for maior
                maxLen = (maxLen > 1 + dfs(matrix, nr, nc)) ? maxLen : (1 + dfs(matrix, nr, nc));
            }
        }
    }

    // Armazena o resultado calculado na matriz de memoização
    memo[r][c] = maxLen;

    // Retorna o comprimento máximo encontrado a partir desta célula
    return maxLen;
}

int longestIncreasingPath(int **matrix, int matrixSize, int *matrixColSize) {
    rows = matrixSize;
    
    // Verifica se a matriz está vazia
    if (rows == 0) {
        return 0;
    }
    cols = matrixColSize[0]; // Assume que todas as linhas têm o mesmo número de colunas

    // Aloca a matriz de memoização e inicializa com zeros
    memo = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        memo[i] = (int *)calloc(cols, sizeof(int)); // calloc inicializa com zeros
    }

    // Variável para armazenar o comprimento máximo geral encontrado
    int overallMax = 0;

    // Percorre todas as células da matriz
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Calcula o caminho crescente mais longo a partir da célula (i, j)
            // e atualiza overallMax se for maior
            int currentPathLen = dfs(matrix, i, j);
            overallMax = (overallMax > currentPathLen) ? overallMax : currentPathLen;
        }
    }

    // Libera a memória alocada para a matriz de memoização
    for (int i = 0; i < rows; i++) {
        free(memo[i]);
    }
    free(memo);

    // Retorna o comprimento máximo global encontrado
    return overallMax;
}