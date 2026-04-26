#include "main.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int score_file_format(void)
{
	int    fd;
	char   buf[1024];
	char **strs;
	int    i;
	int    j;

	fd = open(SCORE_FILE, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buf, 1024) < 0)
	{
		close(fd);
		return (-1);
	}
	strs = ft_split(buf, '\n');
	if (!strs)
	{
		close(fd);
		return (-1);
	}
	for (i = 0; strs[i]; i++)
	{
		if (i > 0 && ft_atoi(strs[i]) > ft_atoi(strs[i - 1]))
		{
			for (i = 0; strs[i]; i++)
				free(strs[i]);
			free(strs);
			close(fd);
			return (0);
		}
		for (j = 0; strs[i][j]; j++)
		{
			if (strs[i][j] < '0' || strs[i][j] > '9')
			{
				for (i = 0; strs[i]; i++)
					free(strs[i]);
				free(strs);
				close(fd);
				return (0);
			}
		}
	}
	for (i = 0; strs[i]; i++)
		free(strs[i]);
	free(strs);
	close(fd);
	return (1);
}

int get_10_best_score(int tab[10])
{
	int    fd;
	char   buf[1024];
	char **strs;
	int    i;

	fd = open(SCORE_FILE, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buf, 1024) < 0)
	{
		close(fd);
		return (-1);
	}
	strs = ft_split(buf, '\n');
	for (i = 0; strs[i]; i++)
		tab[i] = ft_atoi(strs[i]);
	for (i = 0; strs[i]; i++)
		free(strs[i]);
	free(strs);
	close(fd);
	return (1);
}

int game_best_score(int board_size, int board[board_size][board_size])
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
	int   fd = -1;
	char *str_score;
	int   tab[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int   res[11];
	int   i;

	if (score_file_format() > 0)
		fd = open(SCORE_FILE, O_WRONLY);
	if (score_file_format() <= 0 || fd < 0)
	{
		if (fd >= 0)
			close(fd);
		fd = open(SCORE_FILE, O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
			return (-1);
	}
	if (get_10_best_score(tab) < 0)
	{
		close(fd);
		return (-1);
	}
	if (score < tab[9])
	{
		close(fd);
		return (0);
	}
	for (i = 0; i < 11; i++)
	{
		if (score > tab[i])
		{
			res[i] = score;
			while (i < 10)
			{
				res[i + 1] = tab[i];
				i++;
			}
			break;
		}
		res[i] = tab[i];
	}
	for (i = 0; i < 10 && res[i] > 0; i++)
	{
		str_score = ft_itoa(res[i]);
		write(fd, str_score, ft_strlen(str_score));
		if (i < 9 && res[i + 1] > 0)
			write(fd, "\n", 1);
		free(str_score);
	}
	close(fd);
	return (1);
}
