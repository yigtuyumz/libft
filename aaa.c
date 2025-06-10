#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char reverse_bits(unsigned char b)
{
	unsigned char rev = 0;
	for (int i = 0; i < 8; i++)
	{
		rev <<= 1;
		rev |= (b & 1);
		b >>= 1;
	}
	return rev;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		write(STDERR_FILENO, "Usage: program input_file output_file\n", 38);
		return 1;
	}

	int fin = open(argv[1], O_RDONLY);
	if (fin < 0)
	{
		perror("Input file open error");
		return 1;
	}

	int fout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0400);
	if (fout < 0)
	{
		perror("Output file open error");
		close(fin);
		return 1;
	}

	unsigned char buf;
	ssize_t n;

	while ((n = read(fin, &buf, 1)) > 0)
	{
		unsigned char reversed = reverse_bits(buf);
		if (write(fout, &reversed, 1) != 1)
		{
			perror("Write error");
			close(fin);
			close(fout);
			return 1;
		}
	}

	if (n < 0)
	{
		perror("Read error");
		close(fin);
		close(fout);
		return 1;
	}

	close(fin);
	close(fout);

	return 0;
}
