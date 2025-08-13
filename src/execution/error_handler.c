#include "minishell.h"

void    runtime_err(char *msg)
{
    t_allocators *allocs = get_allocators();
    ft_putstr_fd("minishell:", 2);
    if (msg)
    {
        ft_putstr_fd(msg, 2);
        ft_putstr_fd(":", 2);
    }
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    clean_up(allocs->global, true);
    clean_up(allocs->tmp, false);
    exit(errno);
}