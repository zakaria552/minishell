#include "minishell.h"

void    env(void)
{
    t_local_vars *vars;
    t_env_var *var;
    int i;

    i = -1;
    vars = get_local_vars();
    while (++i < vars->envp->size)
    {
        var = vars->envp->get(vars->envp, i);
        if (var->value)
            ft_printf("%s\n", var->joint);
    }
    vars->status = 0;
}
