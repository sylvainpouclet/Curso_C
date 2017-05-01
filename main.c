#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
	int i = 0;
	struct world w;

	world_init(&w);

	do {
		printf("\033cIteration %d\n", i++);
		world_print(&w);
		world_step(&w);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;	
}