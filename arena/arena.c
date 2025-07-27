#include "arena.h"
#include <string.h>

t_arena *new_arena(size_t size)
{
    t_arena *arena;

    arena = malloc(sizeof(t_arena));
    if (!arena)
        return (NULL);
    arena->size = size;
    arena->off = 0;
    arena->buffer = malloc(arena->size);
    if (!arena->buffer)
    {
        free(arena);
        return (NULL);
    }
    return (arena);
}

void *arena_alloc(t_arena *arena, size_t size)
{
    const size_t prev_off = arena->off;
    void *new_buffer;

    if (arena->size - arena->off < size)
    {
        new_buffer = malloc(arena->size * 2);
        if (!new_buffer)
            return (NULL);
        arena->size = arena->size * 2;
        memmove(new_buffer, arena->buffer, arena->off);
        free(arena->buffer);
        arena->buffer = new_buffer;
    }
    arena->off += size;
    return (arena->buffer + prev_off);
}

void destroy_arena(t_arena *arena)
{
    free(arena->buffer);
    free(arena);
}