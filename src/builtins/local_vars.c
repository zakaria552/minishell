#include "minishell.h"

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
    tmp = ft_strrchr(envp_var, '=');
    tmp++;
    var->value = arena->alloc(arena, ft_strlen(tmp) + 1, tmp);
    var->joint = arena->alloc(arena, ft_strlen(envp_var) + 1, envp_var);
    return var;
}
