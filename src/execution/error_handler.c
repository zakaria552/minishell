#include "minishell.h"

void    runtime_err(char *msg)
{
    ft_printf("minishell: ");
    if (msg)
        ft_printf("%s:", msg);
    ft_printf("%s\n", strerror(errno));
}