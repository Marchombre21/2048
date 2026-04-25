#include "main.h"

int can_move_dir(int board_size, int board[board_size][board_size], char dir)
{
	int i;
	int j;
	int zero_reached;

	if (dir == 'T')
	{
		for (i = 0; i < board_size; i++)
		{
			zero_reached = 0;
			for (j = 0; j < board_size; j++)
			{
				if ((zero_reached && board[i][j]) || (j < board_size - 1 && board[i][j] == board[i][j + 1] && board[i][j] != 0))
					return (1);
				if (!zero_reached && !board[i][j])
					zero_reached = 1;
			}
		}
	}
	else if (dir == 'B')
	{
		for (i = 0; i < board_size; i++)
		{
			zero_reached = 0;
			for (j = board_size - 1; j >= 0; j--)
			{
				if ((zero_reached && board[i][j]) || (j > 0 && board[i][j] == board[i][j - 1] && board[i][j] != 0))
					return (1);
				if (!zero_reached && !board[i][j])
					zero_reached = 1;
			}
		}
	}
	else if (dir == 'L')
	{
		for (j = 0; j < board_size; j++)
		{
			zero_reached = 0;
			for (i = 0; i < board_size; i++)
			{
				if ((zero_reached && board[i][j]) || (i < board_size - 1 && board[i][j] == board[i + 1][j] && board[i][j] != 0))
					return (1);
				if (!zero_reached && !board[i][j])
					zero_reached = 1;
			}
		}
	}
	else if (dir == 'R')
	{
		for (j = 0; j < board_size; j++)
		{
			zero_reached = 0;
			for (i = board_size - 1; i >= 0; i--)
			{
				if ((zero_reached && board[i][j]) || (i > 0 && board[i][j] == board[i - 1][j] && board[i][j] != 0))
					return (1);
				if (!zero_reached && !board[i][j])
					zero_reached = 1;
			}
		}
	}
	else
		return (-1);
	return (0);
}

int is_loose(int board_size, int board[board_size][board_size])
{
	if (!can_move_dir(board_size, board, 'T') && !can_move_dir(board_size, board, 'B') && !can_move_dir(board_size, board, 'L') && !can_move_dir(board_size, board, 'R'))
	{
		return (1);
	}
	return (0);
}

int is_win(int board_size, int board[board_size][board_size])
{
	int i;
	int j;

	for (i = 0; i < board_size; i++)
	{
		for (j = 0; j < board_size; j++)
		{
			if (board[i][j] >= WIN_VALUE)
				return (1);
		}
	}
	return (0);
}

