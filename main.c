#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// TODO: Crea dos macros con el tamaño horizontal y vertical del mundo: OK
#define W_SIZE_X 10
#define W_SIZE_Y 10

void world_init(bool *w_init);
void world_print(bool *w_print);
void world_step(bool *w1_step , bool *w2_step);
int world_count_neighbors(bool *w_count , int X_count , int Y_count);
bool world_get_cell(bool *w_get , int X_get , int Y_get);
void world_copy(bool *w1_copy , bool *w2_copy);

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

		// TODO: Itera: OK
		world_step(puntero_world1 , puntero_world2);

	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void world_init(bool *w_init)
{
	// TODO: Poner el mundo a false: OK
	for (int i = 0 ; i < (W_SIZE_Y * W_SIZE_X) ; i++)
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

void world_step(bool *w1_step , bool *w2_step)
{
	/*
	 * TODO: OK
	 * - Recorrer el mundo célula por célula comprobando si nace, sobrevive
	 *   o muere.
	 *
	 * - No se puede cambiar el estado del mundo a la vez que se recorre:
	 *   Usar un mundo auxiliar para guardar el siguiente estado.
	 *
	 * - Copiar el mundo auxiliar sobre el mundo principal
	 */
	for (int i = 0 ; i < W_SIZE_Y ; i++)
	{
		for (int j = 0; j < W_SIZE_X; ++j)
		{
		*(w2_step + (i * W_SIZE_X + j)) = world_get_cell(w1_step , j , i);
		}
	}

	//Copiar el mundo auxiliar sobre el mundo principal: OK

	world_copy(w1_step , w2_step);

}

int world_count_neighbors(bool *w_count , int X_count , int Y_count)
{
	int counter = 0;

	if ( *(w_count + (Y_count * W_SIZE_X) + X_count - 1) && (X_count > 0))
	{
		counter++;
	}
	if ( *(w_count + (Y_count * W_SIZE_X) + X_count + 1) && (X_count < W_SIZE_X - 1))
	{
		counter++;
	}
	if ( *(w_count + ((Y_count - 1)  * W_SIZE_X) + X_count - 1) && (X_count > 0) && (Y_count > 0))
	{
		counter++;
	}
	if ( *(w_count + ((Y_count - 1)  * W_SIZE_X) + X_count) && (Y_count > 0))
	{
		counter++;
	}
	if ( *(w_count + ((Y_count - 1)  * W_SIZE_X) + X_count +1) && (Y_count > 0))
	{
		counter++;
	}
	if ( *(w_count + ((Y_count + 1)  * W_SIZE_X) + X_count - 1)  && (X_count > 0) && (Y_count < W_SIZE_Y - 1))
	{
		counter++;
	}
	if ( *(w_count + ((Y_count + 1)  * W_SIZE_X) + X_count) && (Y_count < W_SIZE_Y - 1))
	{
		counter++;
	}
	if ( *(w_count + ((Y_count + 1)  * W_SIZE_X) + X_count +1) && (X_count < W_SIZE_X - 1 ) && (Y_count < W_SIZE_Y - 1 ))
	{
		counter++;
	}

	// Devuelve el número de vecinos: OK
	return counter;
}

bool world_get_cell(bool *w_get , int X_get , int Y_get)
{
	/*
	 * TODO: Devuelve el estado de la célula de posición indicada: OK
	 * (¡cuidado con los límites del array!)
	 */
	int neighbors = world_count_neighbors(w_get , X_get , Y_get);
	
	if ( *(w_get + (Y_get * W_SIZE_X) + X_get) && ( neighbors == 2 || neighbors == 3) || !*(w_get + (Y_get * W_SIZE_X) + X_get) && neighbors == 3 )
	 {
	 	return true;
	 } 

	 return false;
}

void world_copy(bool *w1_copy , bool *w2_copy)
{
	// TODO: copia el mundo segundo mundo sobre el primero: OK
	for (int i = 0 ; i < (W_SIZE_Y * W_SIZE_X) ; i++)
		{
			*(w1_copy + i) = *(w2_copy + i);
		}
		
	
}
