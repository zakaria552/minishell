#include "minishell.h"

static void    bubble_sort_vars(t_vector *sorted, t_env_var *var, t_env_var *var_n, t_env_var *tmp);

t_local_vars *get_local_vars()
{
    static  t_local_vars vars;
    return (&vars);
}

void    init_local_vars(char **envp)
{
    const t_allocators *allocs = get_allocators();
    t_local_vars *vars = get_local_vars(); 
    t_env_var *var;

    if (vars->envp)
        return;
    vars->envp = init_vector(INIT_VECTOR_SIZE, NULL, allocs->global);
    while (envp && *envp)
    {
        var = init_var(*envp, allocs->global);
        vars->envp->push(vars->envp, var);
        envp++;
    }
    vars->status = 0;
    vars->unset = remove_var;
    vars->get = get_var;
    vars->set = set_var;
    vars->stdin_cpy = -1;
    vars->stdout_cpy = -1;
	vars->pwd = pwd_to_string(allocs->global);
    update_shell_level(vars);
}

t_env_var    *init_var(char *envp_var, t_arena *arena)
{
    t_env_var *var;
    char *tmp;
    int len;

    var = arena->alloc(arena, sizeof(t_env_var), NULL);
    len = 0;
    while (envp_var[len] && envp_var[len] != '=')
        len++;
    var->variable = arena->alloc(arena, len + 1, NULL);
    while (--len >= 0)
        var->variable[len] = envp_var[len];
    tmp = ft_strchr(envp_var, '=');
    if (tmp && *tmp)
        var->value = arena->alloc(arena, ft_strlen(tmp + 1) + 1, tmp + 1);
    else
        var->value = NULL;
    var->joint = arena->alloc(arena, ft_strlen(envp_var) + 1, envp_var);
    return var;
}

t_vector *sorted_envp_vars(t_local_vars *vars)
{
    const t_arena *arena = get_allocators()->prompt;
    t_vector *sorted;
    t_env_var *var = {0};
    t_env_var *var_n = {0};
    t_env_var tmp = {0};
    int i;

    i = -1;
    sorted = init_vector(vars->envp->size, NULL, (t_arena  *)arena);
    while (++i < vars->envp->size)
        sorted->push(sorted, vars->envp->get(vars->envp, i)); 
    bubble_sort_vars(sorted, var, var_n, &tmp);
    return sorted;
}

static void    bubble_sort_vars(t_vector *sorted, t_env_var *var, t_env_var *var_n, t_env_var *tmp)
{
    int i;
    int j;

    i = -1;
    while (++i < sorted->size)
    {
        j = -1;
        while (++j < (sorted->size - i))
        {
            var = sorted->get(sorted, j);
            var_n = sorted->get(sorted, j + 1);
            if (!var || !var_n || ft_strncmp(var->variable, var_n->variable,
                 ft_strlen(var_n->variable)) < 0)
                continue;
            ft_memcpy(tmp, var, sizeof(t_env_var));
            ft_memcpy(var, var_n, sizeof(t_env_var));
            ft_memcpy(var_n, tmp, sizeof(t_env_var));
        }
    }
}
