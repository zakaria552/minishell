#include "minishell.h"

void    export(t_cmd *cmd)
{   
    t_local_vars *vars;
    int i;

    i = -1;
    vars = get_local_vars();
    while (++i < cmd->args->size)
        vars->set(cmd->args->get(cmd->args, i));
    i = -1;
    while (++i < vars->envp->size && cmd->args->size == 0)
        ft_printf("declare -x %s\n", ((t_env_var *)vars->envp->get(vars->envp, i))->joint);
    vars->status = 0;
}

void    unset(t_cmd *cmd)
{
    t_local_vars *vars;
    int i;

    i = -1;
    vars = get_local_vars();
    while (++i < cmd->args->size)
        vars->unset(cmd->args->get(cmd->args, i));
    vars->status = 0;
}

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
        ft_printf("%s\n", var->joint);
    }
    vars->status = 0;
}
