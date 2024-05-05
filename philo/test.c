#include "philo.h"
#include <string.h>

int main(void)
{
	char *str = "a";
	char *str2 = "";
	printf("%d\n", ft_strcmp(str, str2));
	printf("%d\n", strcmp(str, str2));
}