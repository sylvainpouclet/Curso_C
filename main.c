#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

int main()
{

	int i = 0;

	struct world *w  = world_alloc(W_SIZE_X , W_SIZE_Y);
	if (!w) {
		perror("Can't allocate world");
		return EXIT_FAILURE;
	}

	do {
		printf("\033cIteration %d\n", i++);
		world_print(w);
		world_iterate(w);

	} while (getchar() != 'q');

	world_free(w);

	return EXIT_SUCCESS;	
}