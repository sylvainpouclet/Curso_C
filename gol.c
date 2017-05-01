#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

void world_init(struct world *w)
{
	// Init a false del mundo
	for (int i = 0 ; i < W_SIZE_X ; i++)
		for (int j = 0; j < W_SIZE_Y; ++j)
			*(w->w_1[0] + (i * W_SIZE_Y + j)) = false;
	
	// Init de un Glider	
	*(w->w_1[0] + (0 * W_SIZE_Y + 1)) = true;
	*(w->w_1[0] + (1 * W_SIZE_Y + 2)) = true;	
	*(w->w_1[0] + (2 * W_SIZE_Y + 0)) = true;
	*(w->w_1[0] + (2 * W_SIZE_Y + 1)) = true;	
	*(w->w_1[0] + (2 * W_SIZE_Y + 2)) = true;	
}

void world_print(const struct world *w)
{
	for (int i = 0 ; i < W_SIZE_X ; i++) {
		for (int j = 0; j < W_SIZE_Y; ++j)
			printf("%c " , *(w->w_1[0] + (i * W_SIZE_Y + j)) == 0 ? '.' : '#' );	

		printf("\n");	
	}
}

void world_step(struct world *w)
{
	for (int x = 0 ; x < W_SIZE_X ; x++) {
		for (int y = 0; y < W_SIZE_Y; ++y) {
			int neighbors = world_count_neighbors(w, x, y);	
			*(w->w_2[0] + (x * W_SIZE_Y + y)) = (*(w->w_1[0] + (x * W_SIZE_Y + y)) && neighbors == 2) || neighbors == 3;
		}
	}
	// copia del mundo auxiliar al mundo principal
	world_copy(w);
}

int world_count_neighbors(const struct world *w, int x , int y)
{
	int counter = 0;

	counter += world_get_cell(w, x , y - 1);
	counter += world_get_cell(w, x , y + 1);
	counter += world_get_cell(w, x + 1, y - 1);
	counter += world_get_cell(w, x + 1, y);
	counter += world_get_cell(w, x + 1, y + 1);
	counter += world_get_cell(w, x - 1, y - 1);
	counter += world_get_cell(w, x - 1, y);
	counter += world_get_cell(w, x - 1, y + 1);

	return counter;
}

bool world_get_cell(const struct world *w, int x , int y)
{
	// redireccion de la coordenada para un mundo toroidal
	if (x == -1)
		x = W_SIZE_X - 1;
	else if (x == W_SIZE_X)
		x = 0;

	if (y == -1)
		y = W_SIZE_Y - 1;
	else if (y == W_SIZE_Y)
		y = 0;

	return *(w->w_1[0] + (x * W_SIZE_Y + y));
}

void world_copy(struct world *w)
{
	for (int i = 0 ; i < W_SIZE_X ; i++)
		for (int j = 0; j < W_SIZE_Y; ++j)
			*(w->w_1[0] + (i * W_SIZE_Y + j)) = *(w->w_2[0] + (i * W_SIZE_Y + j));
}