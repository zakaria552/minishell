#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>

typedef struct s_arena
{
    void *buffer;
    size_t size;
    size_t off;
} t_arena;

#endif
