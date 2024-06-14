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

int main(void)
{
	size_t len = ft_strlen("8cBVVfQNauvri6K7dG6IT4wGjlZSHzJbtex62OcC6OXT1wCED8");
	printf("%ld\n", len);
}