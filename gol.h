#ifndef _GOL_H_
#define _GOL_H_

#define W_SIZE_X 10
#define W_SIZE_Y 10

struct world;

struct world *world_alloc(int size_x, int size_y);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);


#endif