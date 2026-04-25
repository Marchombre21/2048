#include "main.h"
#include <stdlib.h>
#include <time.h>

void add_nb(int board_size, int board[board_size][board_size])
{
	int rand_nb;
	int x;
	int y;
	int empty_cell = 0;

	for (x = 0; x < board_size; x++)
		for (y = 0; y < board_size; y++)
			if (board[x][y] == 0)
				empty_cell++;
	if (is_loose(board_size, board))
		return;
	srand(time(NULL));
	rand_nb = rand() % 10;
	if (!rand_nb)
		rand_nb = 4;
	else
		rand_nb = 2;
	for (x = 0; x < board_size; x++)
	{
		for (y = 0; y < board_size; y++)
		{
			if (board[x][y] == 0)
				empty_cell--;
			if (empty_cell == 0)
			{
				board[x][y] = rand_nb;
				return;
			}
		}
	}
}

void up(int board_size, int board[board_size][board_size])
{
	int temp[board_size];
	int i;
	int j;
	int k;

	for (k = 0; k < board_size; k++)
		temp[k] = 0;
	for (i = 0; i < board_size; i++)
	{
		k = 0;
		for (j = 0; j < board_size; j++)
		{
			if (board[i][j] > 0)
			{
				temp[k] = board[i][j];
				k++;
			}
		}
		for (k = 0; k < board_size - 1; k++)
		{
			if (temp[k] == temp[k + 1])
			{
				temp[k] *= 2;
				temp[k + 1] = 0;
			}
		}
		for (j = 0; j < board_size; j++)
			board[i][j] = 0;
		j = 0;
		for (k = 0; k < board_size; k++)
		{
			if (temp[k])
			{
				board[i][j] = temp[k];
				j++;
			}
		}
		for (k = 0; k < board_size; k++)
			temp[k] = 0;
	}
	add_nb(board_size, board);
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
	add_nb(board_size, board);
}

void left(int board_size, int board[board_size][board_size])
{
	int temp[board_size];
	int i;
	int j;
	int k;

	for (k = 0; k < board_size; k++)
		temp[k] = 0;
	for (j = 0; j < board_size; j++)
	{
		k = 0;
		for (i = 0; i < board_size; i++)
		{
			if (board[i][j] > 0)
			{
				temp[k] = board[i][j];
				k++;
			}
		}
		for (k = 0; k < board_size - 1; k++)
		{
			if (temp[k] == temp[k + 1])
			{
				temp[k] *= 2;
				temp[k + 1] = 0;
			}
		}
		for (i = 0; i < board_size; i++)
			board[i][j] = 0;
		i = 0;
		for (k = 0; k < board_size; k++)
		{
			if (temp[k])
			{
				board[i][j] = temp[k];
				i++;
			}
		}
		for (k = 0; k < board_size; k++)
			temp[k] = 0;
	}
	add_nb(board_size, board);
}

void right(int board_size, int board[board_size][board_size])
{
	int temp[board_size];
	int i;
	int j;
	int k;

	for (k = 0; k < board_size; k++)
		temp[k] = 0;
	for (j = 0; j < board_size; j++)
	{
		k = board_size - 1;
		for (i = board_size - 1; i >= 0; i--)
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
		for (i = 0; i < board_size; i++)
			board[i][j] = 0;
		i = board_size - 1;
		for (k = board_size - 1; k >= 0; k--)
		{
			if (temp[k])
			{
				board[i][j] = temp[k];
				i--;
			}
		}
		for (k = 0; k < board_size; k++)
			temp[k] = 0;
	}
	add_nb(board_size, board);
}
