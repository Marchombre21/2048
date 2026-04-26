#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void *ft_calloc(size_t nmemb, size_t size)
{
	void *all_mem;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	all_mem = malloc(size * nmemb);
	if (!all_mem)
		return (NULL);
	ft_bzero(all_mem, nmemb * size);
	return (all_mem);
}

static size_t strs_size(const char *s, unsigned char c)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if ((s[j] != c && j == 0) || (s[j] != c && s[j - 1] == c))
			i++;
		j++;
	}
	return (i);
}

static int next_match(char *str, unsigned char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void clear_strs(char **strs)
{
	size_t i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char **ft_split(char const *s, char c)
{
	char **strs;
	int    i;
	int    j;

	if (!s)
		return (NULL);
	strs = ft_calloc(sizeof(char *), strs_size(s, c) + 1);
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if ((s[j] != c && j == 0) || (s[j] != c && s[j - 1] == c))
		{
			strs[i] = ft_substr(&s[j], 0, next_match((char *) &s[j], c));
			if (!strs[i++])
			{
				clear_strs(strs);
				return (NULL);
			}
		}
		j++;
	}
	return (strs);
}
