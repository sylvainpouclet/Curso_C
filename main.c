#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"
#include "config.h"

int main(int argc, char *argv[])
{
	int i = 0;
	bool flag = false;
	
	struct config config;
	struct world * w;
 
	if (!config_parse_argv(&config, argc, argv)) {
		printf("ERROR\n");
		config_print_usage(argv[0]);
		return EXIT_FAILURE;
	} else if (config.show_help){
		config_print_usage(argv[0]);
		return EXIT_SUCCESS;
	}
 
	w = world_alloc(&config);
	if (!w) {
		perror("Can't allocate world");
		return EXIT_FAILURE;
	}
 
	do {		
		if (flag)
			world_iterate(w);

		printf("\033cIteration %d\n", i++);  
		world_print(w);
		flag = true;

	} while (getchar() != 'q');
 
 	if (config.flag_save)
 		world_save(&config, w);

	world_free(w);

	return EXIT_SUCCESS;
}