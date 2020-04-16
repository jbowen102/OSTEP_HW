#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int *data = malloc(sizeof(int)*100);

	data[99] = 323;
	printf("data[99]: %d\n", data[99]);
	int *new_data = realloc(data, 200);

	data[199] = 88;
	printf("data[199]: %d\n", new_data[199]);
	// printf("data[2]: %d\n", data[2]);

	free(data);
	return 0;
}
