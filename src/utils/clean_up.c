#include "minishell.h"

void    clean_up(t_arena *arena, bool clean_history)
{
    arena->destroy(arena);
    if (clean_history)
        clear_history();
}

void	ft_error(char *msg)
{
	ft_printf("minishell: %s\n", msg);
}

void    clean_exit(t_arena *arena, int err_code, char *msg)
{
    if (arena)
        clean_up(arena, true);
    errno = err_code;
    if (msg)
        ft_printf("minishell: %s", msg);
    exit(errno);
}
