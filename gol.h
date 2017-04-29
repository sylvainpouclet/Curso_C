#ifndef _GOL_H_
#define _GOL_H_

#define W_SIZE_X 10
#define W_SIZE_Y 10

void world_init(bool world[W_SIZE_X][W_SIZE_Y]);
void world_print(bool world[W_SIZE_X][W_SIZE_Y]);
void world_step(bool world1[W_SIZE_X][W_SIZE_Y] , bool world2[W_SIZE_X][W_SIZE_Y]);
int world_count_neighbors(bool world[W_SIZE_X][W_SIZE_Y], int x, int y);
bool world_get_cell(bool world[W_SIZE_X][W_SIZE_Y], int x, int y);
void world_copy(bool world1[W_SIZE_X][W_SIZE_Y], bool world2[W_SIZE_X][W_SIZE_Y]);

#endif