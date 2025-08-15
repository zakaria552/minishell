#include "minishell.h"

t_env_var    *get_var(char *variable)
{
    const t_local_vars *vars = get_local_vars();
    t_env_var *var;
    int i;
    
    i = -1;
    while (++i < vars->envp->size)
    {
        var = vars->envp->get(vars->envp, i);
        if (ft_strncmp(var->variable, variable, ft_strlen(var->variable)) == 0)
        {
            ft_printf("%s\n", var->joint);
            return var;
        }
    }
    return NULL;
}

void    remove_var(char *variable)
{
    const t_local_vars *vars = get_local_vars();
    t_env_var *var;
    int i;
    
    i = -1;
    while (++i < vars->envp->size)
    {
        var = vars->envp->get(vars->envp, i);
        if (ft_strncmp(var->variable, variable, ft_strlen(var->variable)) == 0)
        {
            vars->envp->remove(vars->envp, i);
            return;
        }
    }
}

void    set_var(char *env_var)
{
    const t_allocators *allocs = get_allocators();
    const t_local_vars *vars = get_local_vars();
    t_env_var *var;
    int i;

    i = -1; 
    while (++i < vars->envp->size)
    {
        var = vars->envp->get(vars->envp, i);
        if (ft_strncmp(var->joint, env_var, ft_strlen(var->variable) + 1) == 0)
        {
            vars->unset(var->variable);
            break;
        }
    }
    var = init_var(env_var, allocs->global);
    vars->envp->push(vars->envp, var);
}