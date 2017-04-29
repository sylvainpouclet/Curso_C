#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

void world_init(bool world[W_SIZE_X][W_SIZE_Y])
{
	// Init a false del mundo
	for (int i = 0 ; i < W_SIZE_X ; i++)
		for (int j = 0; j < W_SIZE_Y; ++j)
			world[i][j] = false;

	// Init de un Glider	
	world[0][1] = true;
	world[1][2] = true;	
	world[2][0] = true;
	world[2][1] = true;	
	world[2][2] = true;		
}

void world_print(bool world[W_SIZE_X][W_SIZE_Y])
{
	for (int i = 0 ; i < W_SIZE_X ; i++) {
		for (int j = 0; j < W_SIZE_Y; ++j)
			printf("%c " , world[i][j] == 0 ? '.' : '#' );	

		printf("\n");	
	}
}

void world_step(bool world1[W_SIZE_X][W_SIZE_Y] , bool world2[W_SIZE_X][W_SIZE_Y])
{
	for (int x = 0 ; x < W_SIZE_X ; x++) {
		for (int y = 0; y < W_SIZE_Y; ++y) {
			int neighbors = world_count_neighbors(world1, x, y);	
			world2[x][y] = (world1[x][y] && neighbors == 2) || neighbors == 3;
		}
	}
	// copia del mundo auxiliar al mundo principal
	world_copy(world1 , world2);
}

int world_count_neighbors(bool world[W_SIZE_X][W_SIZE_Y] , int x , int y)
{
	int counter = 0;

	counter += world_get_cell(world, x , y - 1);
	counter += world_get_cell(world, x , y + 1);
	counter += world_get_cell(world, x + 1, y - 1);
	counter += world_get_cell(world, x + 1, y);
	counter += world_get_cell(world, x + 1, y + 1);
	counter += world_get_cell(world, x - 1, y - 1);
	counter += world_get_cell(world, x - 1, y);
	counter += world_get_cell(world, x - 1, y + 1);

	return counter;
}

bool world_get_cell(bool world[W_SIZE_X][W_SIZE_Y] , int x , int y)
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

	return world[x][y];
}

void world_copy(bool world1[W_SIZE_X][W_SIZE_Y] , bool world2[W_SIZE_X][W_SIZE_Y])
{
	for (int i = 0 ; i < W_SIZE_X ; i++)
		for (int j = 0; j < W_SIZE_Y; ++j)
			world1[i][j] = world2[i][j];	
}