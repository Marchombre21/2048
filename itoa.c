#include <stdlib.h>

static size_t count_digits(int n)
{
	size_t size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static void insert_char(char *str, unsigned int nbr, size_t index)
{
	while (nbr)
	{
		str[index--] = nbr % 10 + '0';
		nbr /= 10;
	}
}

char *ft_itoa(int n)
{
	unsigned int nbr;
	char        *str;
	size_t       size;

	nbr = n;
	if (n < 0)
		nbr = n * -1;
	size = count_digits(n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (nbr == 0)
		str[0] = '0';
	else
	{
		if (n < 0)
			str[0] = '-';
		insert_char(str, nbr, size - 1);
	}
	return (str);
}
