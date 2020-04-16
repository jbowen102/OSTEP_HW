#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int *data = malloc(sizeof(int)*100);

	free(data);

	printf("data[2]: %d\n", data[2]);
	return 0;
}
