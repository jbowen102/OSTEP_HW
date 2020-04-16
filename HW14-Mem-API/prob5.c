#include <stdlib.h>

int main(int argc, char* argv[])
{
	int *data = malloc(sizeof(int)*100);

	data[100] = 0;

	free(data);
	return 0;
}
