#include "minishell.h"

void    clean_up(t_arena *arena, bool clean_history)
{
    arena->destroy(arena);
    if (clean_history)
        clear_history();
}

void    clean_exit(t_arena *arena, int err_code, char *msg)
{
    if (arena)
        clean_up(arena, true);
    errno = err_code;
    if (msg)
        ft_printf("Minishell: %s", msg);
    exit(errno);
}