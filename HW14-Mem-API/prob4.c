#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char *mem_spot = malloc(sizeof(char)*10);

	mem_spot = "character";
	printf("%s\n", mem_spot);

	// free(mem_spot);
	return 0;
}
