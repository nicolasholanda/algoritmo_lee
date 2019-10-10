#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* N�mero de linhas do labirinto */
#define N 10
/* N�mero de colunas do labirinto */
#define M 10

/* Maior valor que um int pode guardar */
#define INT_MAX 2147483647

/* Todas as combina��es de movimentos poss�veis:
 * esquerda, cima, baixo e direita, respectivamente). */
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };


/* Retorna 1 se a posi��o (row, col) � 1 e n�o foi visitada;
 * retorna 0 caso contr�rio. */
int isValid(int mat[][N], int visited[][N], int row, int col) {
	return (row >= 0) && (row < M) && (col >= 0) && (col < N)
		&& mat[row][col] && !visited[row][col];
}

/* Recebe uma matriz e seta todos os elementos para 0 */
void initialize_array(int arr[N][M]) {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
        arr[i][j] = 0;
    }
  }
}


/* Devolve o menor caminho de (i,j) at� (x,y)*/
void lee_maze_solver(int mat[][N], int i, int j, int x, int y) {
    /* Criando array de visitados e o inicializando*/
    int visited[M][N];
	initialize_array(visited);

	/* Criando fila e a iniciando */
	Node q[N*M];
	int head, tail;
    init(&head,&tail);

    /* Marcando o n� inicial como visitado e inserindo ele na fila */
    visited[i][j] = 1;
    Node source = {.x = i, .y = j, .dist = 0};
    enqueue(q, &tail, source);

    /* Armazena o caminho mais longo da origem para o destino */
    int min_dist = INT_MAX;

    /* Enquanto a fila n�o estiver vazia */
    while(!empty(head, tail)) {
        /* Processa o pr�ximo n� da fila */
        Node node = dequeue(q, &head);
        int i = node.x, j = node.y, dist = node.dist;

        /* Se o destino foi encontrado */
        if(i == x && j == y) {
            /* Atualiza min_dist e para */
            min_dist = dist;
            break;
        }

        /* Analisa as quatro movimenta��es poss�veis e empilha cada movimento v�lido */
        for(int k = 0; k < 4; k++) {
            /* Se for poss�vel ir da posi��o atual para a posi��o (i + row[k], j + col[k])*/
            if(isValid(mat, visited, i + row[k], j + col[k])) {
                /* Marque a c�lula como v�lida e empilhe ela */
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
    /* Os elementos que tem 1 representam c�lulas v�lidas;
     * Os que tem 0 representam c�lulas inv�lidas. */
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
