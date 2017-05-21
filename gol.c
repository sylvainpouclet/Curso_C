#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "gol.h"
#include "config.h"

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);

struct world *world_alloc(struct config *config)
{
	
	struct world *w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;
	
	w->size_x = config->size_x;
	w->size_y = config->size_y;

	w->cells[W_WORLD_MAIN] = (bool *)malloc((w->size_x * w->size_y) * sizeof(bool));
	if (!w->cells[W_WORLD_MAIN]){
		free(w);
		return NULL;
	}
	
	w->cells[W_WORLD_AUX] = (bool *)malloc((w->size_x * w->size_y) * sizeof(bool));
	if (!w->cells[W_WORLD_MAIN]){
		free(w->cells[W_WORLD_MAIN]);
		free(w);
		return NULL;
	}
	
 	// Init a false del mundo
	for (int x = 0 ; x < w->size_x ; x++)
		for (int y = 0; y < w->size_y; ++y)
			set_cell(w, W_WORLD_MAIN, x, y, false);

	if (config->init_mode == CFG_DEFAULT){
		// Init de un bloque	
		set_cell(w, W_WORLD_MAIN, 1, 1 , true);
		set_cell(w, W_WORLD_MAIN, 1, 2 , true);
		set_cell(w, W_WORLD_MAIN, 2, 1 , true);
		set_cell(w, W_WORLD_MAIN, 2, 2 , true);
	}
	else if (config->init_mode == CFG_GLIDER){
		// Init de un Glider	
		set_cell(w, W_WORLD_MAIN, 0, 1 , true);
		set_cell(w, W_WORLD_MAIN, 1, 2 , true);
		set_cell(w, W_WORLD_MAIN, 2, 0 , true);
		set_cell(w, W_WORLD_MAIN, 2, 1 , true);
		set_cell(w, W_WORLD_MAIN, 2, 2 , true);
	}
	else if(config->init_mode == CFG_RANDOM){
	// Init a random del mundo
		srand(time(0)); //use current time as seed for random generator

		for (int x = 0 ; x < w->size_x ; x++)
			for (int y = 0; y < w->size_y; ++y)
				set_cell(w, W_WORLD_MAIN, x, y, rand()%2);
	}

	return w;
}

void world_free(struct world *w)
{
	free(w->cells[W_WORLD_MAIN]);
	free(w->cells[W_WORLD_AUX]);
	free(w);
}

void world_print(const struct world *w)
{
	for (int x = 0 ; x < w->size_x ; x++) {
		for (int y = 0; y < w->size_y; ++y)	
		printf("%c " , get_cell(w, x, y) == 0 ? '.' : '#' );
		printf("\n");	
	}
}

void world_iterate(struct world *w)
{
	for (int x = 0 ; x < w->size_x ; x++) {
		for (int y = 0; y < w->size_y; ++y) {
			int neighbors = count_neighbors(w, x, y);
			set_cell(w, W_WORLD_AUX, x, y, ((get_cell(w, x, y) && neighbors == 2) || neighbors == 3) );
		}
	}
	
	// intercambio de puntero entre el mundo auxiliar y el mundo principal
	bool *transfer_mundo;
	transfer_mundo = w->cells[W_WORLD_MAIN];
	w->cells[W_WORLD_MAIN] = w->cells[W_WORLD_AUX];
	w->cells[W_WORLD_AUX] = transfer_mundo;
}

static void fix_coords(const struct world *w, int *x, int *y)
{
	// redireccion de la coordenada para un mundo toroidal
	if (*x == -1)
		*x = w->size_x - 1;
	else if (*x == w->size_x)
		*x = 0;

	if (*y == -1)
		*y = w->size_y - 1;
	else if (*y == w->size_y)
		*y = 0;
}

static bool get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	return *(w->cells[W_WORLD_MAIN] + (x * w->size_y + y));
}

static void set_cell(struct world *w, int buf, int x, int y, bool val)
{
	fix_coords(w, &x, &y);
	*(w->cells[buf] + (x * w->size_y + y)) = val;
}

static int count_neighbors(const struct world *w, int x, int y)
{
	int counter = 0;

	counter += get_cell(w, x , y - 1);
	counter += get_cell(w, x , y + 1);
	counter += get_cell(w, x + 1, y - 1);
	counter += get_cell(w, x + 1, y);
	counter += get_cell(w, x + 1, y + 1);
	counter += get_cell(w, x - 1, y - 1);
	counter += get_cell(w, x - 1, y);
	counter += get_cell(w, x - 1, y + 1);

	return counter;
}




