/****************************************************************************
 *                      ALGORITMO DE LEE (MAZE ROUTER)                      *
 ****************************************************************************
 * O algoritmo de Lee é uma possível solução para problemas de roteamento   *
 * de labirinto com base na busca em largura.                               *
 *                                                                          *
 * Entrada: Uma matriz MxN de 0 e 1 quer epresenta um labirinto,            *
 * onde dígitos 0 são barreiras e dígitos 1 são células disponíveis.        *
 * Uma célula origem (i, j) e uma célula destino (x, y)                     *
 *                                                                          *
 * Saída: O custo da menor rota entre a origem e o destino, caso exista.    *
 * Caso não exista, o algoritmo indicará.                                   *
 *                                                                          *
 * Complexidade Temporal e Espacial: O(MN)                                  *
 *                                                                          *
 * Referência: www.techiedelight.com/lee-algorithm-shortest-path-in-a-maze/ *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* Número de colunas do labirinto */
#define N 10
/* Número de linhas do labirinto */
#define M 10

/* Maior valor que um int pode guardar */
#define INT_MAX 2147483647

/* Todas as combinações de movimentos possíveis:
 * esquerda, cima, baixo e direita, respectivamente). */
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };


/* Retorna 1 se a posição (row, col) é 1 e não foi visitada;
 * retorna 0 caso contrário. */
int isValid(int mat[][N], int visited[][N], int row, int col) {
	return (row >= 0) && (row < M) && (col >= 0) && (col < N)
		&& mat[row][col] && !visited[row][col];
}

/* Recebe uma matriz e seta todos os elementos para 0 */
void initialize_array(int arr[][N]) {
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
        arr[i][j] = 0;
    }
  }
}


/* Devolve o menor caminho de (i,j) até (x,y)*/
void lee_maze_solver(int mat[][N], int i, int j, int x, int y) {
    /* Criando array de visitados e o inicializando*/
    int visited[M][N];
	initialize_array(visited);

	/* Criando fila e a iniciando */
	Node q[N*M];
	int head, tail;
    init(&head,&tail);

    /* Marcando o nó inicial como visitado e inserindo ele na fila */
    visited[i][j] = 1;
    Node source = {.x = i, .y = j, .dist = 0};
    enqueue(q, &tail, source);

    /* Armazena o caminho mais longo da origem para o destino */
    int min_dist = INT_MAX;

    /* Enquanto a fila não estiver vazia */
    while(!empty(head, tail)) {
        /* Processa o próximo nó da fila */
        Node node = dequeue(q, &head);
        int i = node.x, j = node.y, dist = node.dist;

        /* Se o destino foi encontrado */
        if(i == x && j == y) {
            /* Atualiza min_dist e para */
            min_dist = dist;
            break;
        }

        /* Analisa as quatro movimentações possíveis e empilha cada movimento válido */
        for(int k = 0; k < 4; k++) {
            /* Se for possível ir da posição atual para a posição (i + row[k], j + col[k])*/
            if(isValid(mat, visited, i + row[k], j + col[k])) {
                /* Marque a célula como válida e empilhe ela */
                Node element = {.x = i + row[k], .y = j + col[k], .dist = dist + 1};
                visited[i + row[k]][j + col[k]] = 1;
                enqueue(q, &tail, element);
            }
        }
    }

    if(min_dist != INT_MAX) {
        printf("O caminho mais curto de (%d, %d) para (%d, %d) tem tamanho %d.\n", i, j, x, y, min_dist);
    } else {
        printf("Eh impossivel ir de (%d, %d) para (%d, %d).\n", i, j, x, y);
    }
}

int main() {
    /* Os elementos que tem 1 representam células válidas;
     * Os que tem 0 representam células inválidas. */
    int mat[M][N] =
	{
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
	};

	lee_maze_solver(mat, 0, 0, 9, 9);

    return 0;
}
