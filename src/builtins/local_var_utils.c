#include "minishell.h"

static int	str_num_length(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*arena_int_to_string(t_arena *arena, int num)
{
	char	*str_num;
	int		str_len;
	int		sign;
	long	n;

	str_len = str_num_length(num);
	str_num = arena_alloc(arena, (str_len + 1) * sizeof(char), NULL);
	sign = 1;
	n = num;
	if (!str_num)
		return (NULL);
	str_num[str_len] = '\0';
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	while (--str_len >= 0)
	{
		str_num[str_len] = n % 10 + '0';
		n = n / 10;
		if (str_len == 0 && sign < 0)
			str_num[0] = '-';
	}
	return (str_num);
}

t_env_var    *get_var(char *variable)
{
    const t_local_vars *vars = get_local_vars();
    t_env_var *var;
    int i;
    
    i = -1;
	
    while (++i < vars->envp->size)
    {
        var = vars->envp->get(vars->envp, i);
        if (strmatch(var->variable, variable))
            return var;
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
        if (strmatch(var->variable, variable))
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
        if (strmatch(var->joint, env_var))
        {
            vars->unset(var->variable);
            break;
        }
    }
    var = init_var(env_var, allocs->global);
    if (var)
        vars->envp->push(vars->envp, var);
}
