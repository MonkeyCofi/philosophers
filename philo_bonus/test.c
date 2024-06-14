#include <stdio.h>

size_t	ft_strlen(char *str)
{
	size_t	ret;

	ret = 0;
	if (!str)
		return (0);
	if (!*str)
		return (0);
	return (ft_strlen(str + 1) + 1);
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Enter arguments\n");
		return (1);
	}
	for (int i = 1; av[i]; i++)
		printf("str[%d]: %s. Length: %zu\n", i - 1, av[i], ft_strlen(av[i]));
}