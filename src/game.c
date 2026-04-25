#include "main.h"
#include <stdio.h>

void print_board(int board[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%d", board[j][i]);
		printf("\n");
	}
	printf("\n");
}

void down(int board_size, int board[board_size][board_size])
{
	int temp[board_size];
	int i;
	int j;
	int k;

	for (k = 0; k < board_size; k++)
		temp[k] = 0;
	for (i = 0; i < board_size; i++)
	{
		k = board_size - 1;
		for (j = board_size - 1; j >= 0; j--)
		{
			if (board[i][j] > 0)
			{
				temp[k] = board[i][j];
				k--;
			}
		}
		for (k = board_size - 1; k > 0; k--)
		{
			if (temp[k] == temp[k - 1])
			{
				temp[k] *= 2;
				temp[k - 1] = 0;
			}
		}
		for (j = 0; j < board_size; j++)
			board[i][j] = 0;
		j = board_size - 1;
		for (k = board_size - 1; k >= 0; k--)
		{
			if (temp[k])
			{
				board[i][j] = temp[k];
				j--;
			}
		}
		for (k = 0; k < board_size; k++)
			temp[k] = 0;
	}
}

int main(void)
{
	int board[4][4] = {{4, 2, 0, 2}, {2, 0, 2, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}};

	print_board(board);
	down(4, board);
	print_board(board);
	down(4, board);
	print_board(board);
}
