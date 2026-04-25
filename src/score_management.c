#include "main.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int best_score(int board_size, int board[board_size][board_size])
{
	int best = 0;
	int i;
	int j;

	for (i = 0; i < board_size; i++)
		for (j = 0; j < board_size; j++)
			if (board[i][j] > best)
				best = board[i][j];
	return (best);
}

int save_score(int score)
{
	int   fd;
	char *str_score;

	fd = open(SCORE_FILE, O_WRONLY);
	if (fd < 0)
		return (-1);
	str_score = ft_itoa(score);
	if (!str_score)
		return (close(fd), -1);
	if (write(fd, str_score, ft_strlen(str_score)) < 0)
	{
		free(str_score);
		close(fd);
		return (-1);
	}
	free(str_score);
	close(fd);
	return (0);
}

int get_best_score(void)
{
	int  fd;
	int  best_score;
	char buf[1024];
	int  i;

	for (i = 0; i < 1024; i++)
		buf[i] = '\0';
	fd = open(SCORE_FILE, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buf, 1024) < 0)
		return (close(fd), -1);
	best_score = ft_atoi(buf);
	close(fd);
	return (best_score);
}
