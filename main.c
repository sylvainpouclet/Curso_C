#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// TODO: Crea dos macros con el tamaño horizontal y vertical del mundo: OK
#define W_SIZE_X 10
#define W_SIZE_Y 10

void world_init(bool *w_init);
void world_print(bool *w_print);
void world_step(/* Recibo dos mundos */);
int world_count_neighbors(/* Recibo un mundo y unas coordenadas */);
bool world_get_cell(/* Recibo un mundo y unas coordenadas */);
void world_copy(/* Recibo dos mundos */);

int main()
{
	int i = 0;
	// TODO: Declara dos mundos: OK
	bool world_1[W_SIZE_X][W_SIZE_Y];
	bool *puntero_world1 = &world_1[0][0];

	bool world_2[W_SIZE_X][W_SIZE_Y];
	bool *puntero_world2 = &world_2[0][0];

	// TODO: inicializa el mundo: OK
	world_init(puntero_world1);
	
	do {
		printf("\033cIteration %d\n", i++);
		// TODO: Imprime el mundo: OK
		world_print(puntero_world1);
		
		// TODO: Itera
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void world_init(bool *w_init)
{
	// TODO: Poner el mundo a false: OK
	for (int i = 0 ; i < (W_SIZE_Y * W_SIZE_X ) ; i++)
		{
			*(w_init + i) = false;
		}

	/* TODO: Inicializar con el patrón del glider: OK
	 *           . # .
	 *           . . #
	 *           # # #
	 */
	*(w_init + 1) = true;
	*(w_init + W_SIZE_X + 2 ) = true;	
	*(w_init + 2 * W_SIZE_X ) = true;
	*(w_init + 2 * W_SIZE_X + 1 ) = true;	
	*(w_init + 2 * W_SIZE_X + 2 ) = true;		
}

void world_print(bool *w_print)
{
	// TODO: Imprimir el mundo por consola. Sugerencia: OK
	/*
	 *     . # . . . . . . . .
	 *     . . # . . . . . . .
	 *     # # # . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 */
	for (int i = 0 ; i < W_SIZE_Y ; i++)
	{
		for (int j = 0; j < W_SIZE_X; ++j)
		{
			printf("%c " , *(w_print + (i * W_SIZE_X + j) ) == 0 ? '.' : '#' );	
		}
		printf("\n");
		
	}
}

void world_step(/* Recibo dos mundos */)
{
	/*
	 * TODO:
	 * - Recorrer el mundo célula por célula comprobando si nace, sobrevive
	 *   o muere.
	 *
	 * - No se puede cambiar el estado del mundo a la vez que se recorre:
	 *   Usar un mundo auxiliar para guardar el siguiente estado.
	 *
	 * - Copiar el mundo auxiliar sobre el mundo principal
	 */
}

int world_count_neighbors(/* Recibo un mundo y unas coordenadas */)
{
	// Devuelve el número de vecinos
}

bool world_get_cell(/* Recibo un mundo y unas coordenadas */)
{
	/*
	 * TODO: Devuelve el estado de la célula de posición indicada
	 * (¡cuidado con los límites del array!)
	 */
}

void world_copy(/* Recibo dos mundos */)
{
	// TODO: copia el mundo segundo mundo sobre el primero
}
