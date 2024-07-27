#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i, sum = 0;

	printf("%d\n", argc);
	for (i = 0; i < argc; i++)
	{
		printf("argv[] = %s\n", argv[0]);
	}
	return 0;
}
