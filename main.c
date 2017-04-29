#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
	int i = 0;

	bool world_1[W_SIZE_X][W_SIZE_Y];
	bool world_2[W_SIZE_X][W_SIZE_Y];

	world_init(world_1);
	
	do {
		printf("\033cIteration %d\n", i++);

		world_print(world_1);

		world_step(world_1 , world_2);

	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}


