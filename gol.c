#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "gol.h"
#include "config.h"

struct world
{
	int size_x;
	int size_y;
	bool *cells[2];
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);
static struct world *world_restore(const char *file);
static struct world *world_alloc_size(int size_x, int size_y);
static void init_default(struct world *w);
static void init_glider(struct world *w);
static void init_random(struct world *w);

typedef void (*initializer)(struct world *w);
static const initializer initializers[] = {
	init_default,
	init_glider,
	init_random,
};

struct world *world_alloc(struct config *config)
{	
	struct world *w;

	if (config->restore_file){	
		w = world_restore(config->restore_file);

	} else {
		w = world_alloc_size(config->size_x, config->size_y);

		// Init a false del mundo
		int x, y;
		for (x = 0 ; x < w->size_x ; x++)
			for (y = 0; y < w->size_y; ++y)
				set_cell(w, W_WORLD_MAIN, x, y, false);
		//llamada de la funcion de init
		initializers[config->init_mode](w);
	}
	return w;
}

struct world *world_alloc_size(int size_x, int size_y)
{
	struct world *w = (struct world *)malloc(sizeof(struct world));

	if (!w)
		return NULL;

	w->size_x = size_x;
	w->size_y = size_y;
	
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

	return w;
};

struct world *world_restore(const char *file)
{
		
	FILE *f;	
	f = fopen(file, "r");
	if (!f)
		perror("Error al abrir el fichero para restaurar el mundo\n");
	
	int size_x, size_y;
	fread(&size_x, sizeof(int), 1, f);
	fread(&size_y, sizeof(int), 1, f);

	if ((size_x < 1) | (size_y < 1)){
		perror("Error en las dimensiones del mundo restaurado\n");
		return NULL;
	}

	struct world *w;

	w = world_alloc_size(size_x, size_y);

	fread(w->cells[W_WORLD_MAIN], sizeof(bool), w->size_x * w->size_y, f);

	fclose(f);

	printf("Game restored from file: %s\n", file);	

	return w;
};

void world_free(struct world *w)
{
	free(w->cells[W_WORLD_MAIN]);
	free(w->cells[W_WORLD_AUX]);
	free(w);
}

void world_print(const struct world *w)
{
	int x, y;
	for (x = 0 ; x < w->size_x ; x++) {
		for (y = 0; y < w->size_y; ++y)	
		printf("%c " , get_cell(w, x, y) == 0 ? '.' : '#' );
		printf("\n");	
	}
}

void world_iterate(struct world *w)
{
	int x, y;
	for (x = 0 ; x < w->size_x ; x++) {
		for (y = 0; y < w->size_y; ++y) {
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

void world_save(struct config *config, struct world *w)
{
	FILE *f;
	f = fopen(config->save_file, "w");
	if (!f){
		perror("Error al abrir el fichero para guardar el mundo\n");
		exit(EXIT_FAILURE);
	}
	fwrite(&w->size_x, sizeof(int), 1, f);
	fwrite(&w->size_y, sizeof(int), 1, f);
	fwrite(w->cells[W_WORLD_MAIN], sizeof(bool), (w->size_x * w->size_y), f);

	fclose(f);

	printf("Game saved in file: %s\n", config->save_file);

}

static void init_default(struct world *w)
{
	set_cell(w, W_WORLD_MAIN, 1, 1 , true);	
	set_cell(w, W_WORLD_MAIN, 1, 2 , true);
	set_cell(w, W_WORLD_MAIN, 2, 1 , true);
	set_cell(w, W_WORLD_MAIN, 2, 2 , true);
}

static void init_glider(struct world *w)
{
	// Init de un Glider	
	set_cell(w, W_WORLD_MAIN, 0, 1 , true);
	set_cell(w, W_WORLD_MAIN, 1, 2 , true);
	set_cell(w, W_WORLD_MAIN, 2, 0 , true);
	set_cell(w, W_WORLD_MAIN, 2, 1 , true);
	set_cell(w, W_WORLD_MAIN, 2, 2 , true);	
}

static void init_random(struct world *w)
{
	// Init a random del mundo
	srand(time(0)); //use current time as seed for random generator
	int x, y;
	for (x = 0 ; x < w->size_x ; x++)
		for (y = 0; y < w->size_y; ++y)
			set_cell(w, W_WORLD_MAIN, x, y, rand()%2);
}