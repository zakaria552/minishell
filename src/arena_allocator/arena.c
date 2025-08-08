#include "minishell.h"
#include <string.h>

t_arena *init_arena(size_t size)
{
    t_arena *arena;

    arena = malloc(sizeof(t_arena));
    if (!arena)
        return (NULL);
    arena->size = size;
    arena->offset = 0;
    arena->next = NULL;
    arena->buffer = malloc(arena->size);
    arena->alloc = arena_alloc;
    arena->destroy = destroy_arena;
    if (!arena->buffer)
    {
        free(arena);
        return (NULL);
    }
	ft_memset(arena->buffer, 0, size);
    return (arena);
}

void *arena_alloc(t_arena *arena, size_t size, void *content)
{
    t_arena *tail;
    size_t prev_off;
    size_t new_off;

    tail = tail_arena(arena);
    new_off = allign_p(tail, size);
    if (new_off < tail->size)
    {
        prev_off = tail->offset;
        tail->offset = new_off;
        if (content)
            ft_memcpy((char *)tail->buffer + prev_off, content, size);
        return (tail->buffer + prev_off);
    }
    if (size > ARENA_SIZE)
        tail->next = init_arena(size);
    else
        tail->next = init_arena(ARENA_SIZE);
    if (!tail->next)
        return (NULL);
    tail = tail->next;
    prev_off = tail->offset;
    tail->offset += size;
    if (content)
        ft_memcpy(tail->buffer, content, size);
    return (tail->buffer);
}
