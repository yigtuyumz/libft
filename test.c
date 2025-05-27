#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);

	i = 0;
	while (*(s1 + i) && i < n)
	{
		if (*(s1 + i) != *(s2 + i))
			return (*(s1 + i) - *(s2 + i));
		i++;
	}
	return (*(s1 + i) - *(s2 + i));
}


int	ft_memcmp(const void *s1, const void *s2, size_t n)
{

}

/* strchr ile 42'deki 2 yi bul, memset ile 3'e setle */
int main(int argc, char *argv[])
{
	if (!argv[1] || !argv[2] || !argv[3])
		return (1);
	printf("memcmp_nn %d\n", memcmp(argv[1], argv[2], atoi(argv[3])));
	printf("memcmp_ft %d\n", ft_memcmp(argv[1], argv[2], atoi(argv[3])));

	printf("strncp_nn %d\n", strncmp(argv[1], argv[2], atoi(argv[3])));
	printf("strncp_ft %d\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
	return (0);
}
