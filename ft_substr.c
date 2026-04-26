#include "main.h"
#include <stdint.h>
#include <stdlib.h>

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t i;
	char  *sub_str;
	size_t s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		len = 0;
	else if (s_len < (start + len))
		len = s_len - start;
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
