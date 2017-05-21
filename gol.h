#ifndef _GOL_H_
#define _GOL_H_

#define W_WORLD_MAIN 0
#define W_WORLD_AUX 1
#include "config.h"

struct world;

struct world *world_alloc(struct config *config);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);


#endif