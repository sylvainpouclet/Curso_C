#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"


struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);



struct world *world_alloc(int size_x, int size_y)
{
	struct world *w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;

	w->cells[0] = (bool *)malloc((size_x * size_y) * sizeof(bool));
	if (!w->cells[0])
		return NULL;
	
	w->cells[1] = (bool *)malloc((size_x * size_y) * sizeof(bool));
	if (!w->cells[1])
		return NULL;
	
 	// Init a false del mundo
	for (int x = 0 ; x < W_SIZE_X ; x++)
		for (int y = 0; y < W_SIZE_Y; ++y)
			*(w->cells[0] + (x * W_SIZE_Y + y)) = false;

  	// Init de un Glider	
	*(w->cells[0] + (0 * W_SIZE_Y + 1)) = true;
	*(w->cells[0] + (1 * W_SIZE_Y + 2)) = true;	
	*(w->cells[0] + (2 * W_SIZE_Y + 0)) = true;
	*(w->cells[0] + (2 * W_SIZE_Y + 1)) = true;	
	*(w->cells[0] + (2 * W_SIZE_Y + 2)) = true;

	return w;
}


void world_free(struct world *w)
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}

void world_print(const struct world *w)
{
	for (int x = 0 ; x < W_SIZE_X ; x++) {
		for (int y = 0; y < W_SIZE_Y; ++y)	
		printf("%c " , get_cell(w, x, y) == 0 ? '.' : '#' );
		printf("\n");	
	}
}

void world_iterate(struct world *w)
{
	for (int x = 0 ; x < W_SIZE_X ; x++) {
		for (int y = 0; y < W_SIZE_Y; ++y) {
			int neighbors = count_neighbors(w, x, y);	
			set_cell(w, x, y, ((*(w->cells[0] + (x * W_SIZE_Y + y)) && neighbors == 2) || neighbors == 3) );
		}
	}
	
	// copia del mundo auxiliar al mundo principal
	bool *transfer_mundo;
	transfer_mundo = w->cells[0];
	w->cells[0] = w->cells[1];
	w->cells[1] = transfer_mundo;
}

static void fix_coords(const struct world *w, int *x, int *y)
{
	// redireccion de la coordenada para un mundo toroidal
	if (*x == -1)
		*x = W_SIZE_X - 1;
	else if (*x == W_SIZE_X)
		*x = 0;

	if (*y == -1)
		*y = W_SIZE_Y - 1;
	else if (*y == W_SIZE_Y)
		*y = 0;
}

static bool get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	return *(w->cells[0] + (x * W_SIZE_Y + y));
}

static void set_cell(struct world *w, int x, int y, bool val)
{
	fix_coords(w, &x, &y);
	*(w->cells[1] + (x * W_SIZE_Y + y)) = val;
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




