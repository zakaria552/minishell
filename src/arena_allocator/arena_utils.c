#include "arena.h"

t_arena *tail_arena(t_arena *arena)
{
    while (arena)
    {
        if (!arena->next)
            return (arena);
        arena = arena->next;
    }
    return NULL;
}

void destroy_arena(t_arena *arena)
{
    t_arena *tmp;

    while (arena->next)
    {
        free(arena->buffer);
        tmp = arena;
        arena = arena->next;
        free(tmp);
    }
    free(arena->buffer);
    free(arena);
}

size_t allign_p(t_arena *arena, size_t size)
{
    const size_t modulo = (arena->offset) % ALIGNMENT;

    if (size > modulo && modulo != 0)
        return arena->offset + ALIGNMENT - modulo + size;
    return arena->offset + size;
}
