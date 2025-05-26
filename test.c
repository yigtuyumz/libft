#include <stdio.h>
#include <ctype.h>
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *) s + i) = (unsigned char) c;
		i++;
	}

	return (0);
}

/* strchr ile 42'deki 2 yi bul, memset ile 3'e setle */
int main(void)
{
	char buff[50];
	char buff2[50];
	// int *b = (int *) memset(buff, 'a', 330);
	int *c = (int *) ft_memset(buff2, 'a', 330);
	buff[49] = 0;
	buff2[49] = 0;

	// *b = 0x64656667;

	printf("%s\n", buff);
	printf("%s\n", buff2);

	return (0);
}