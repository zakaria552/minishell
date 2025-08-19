#include "minishell.h"

static bool    invalid_err_msg(char *var);
static bool is_valid_export(char *joint);

void    export(t_cmd *cmd)
{   
    t_local_vars *vars;
    char *arg;
    int i;

    i = -1;
    vars = get_local_vars();
    while (++i < cmd->args->size)
    {
        arg = cmd->args->get(cmd->args, i);
        if (!is_valid_export(arg))
            vars->status = 1;
        else
        {
            vars->set(arg);
            vars->status = 0;
        }
    }
    i = -1;
    while (++i < vars->envp->size && cmd->args->size == 0)
        ft_printf("declare -x %s\n", ((t_env_var *)vars->envp->get(vars->envp, i))->joint);
    if (cmd->args->size == 0)
        vars->status = 0;
}

static bool is_valid_export(char *joint)
{
    int i;

    i = -1;
    if (!joint || *joint == '=' || ft_isdigit(*joint) || !ft_strchr(joint, '='))
        return invalid_err_msg(joint);
    while (joint[++i] != '=') 
    {
        if (ft_isspace(joint[i]))
            return invalid_err_msg(joint);
    }
    return true; 
}

static bool    invalid_err_msg(char *var)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(var, 2);
    ft_putstr_fd("`: not a valid identifier\n", 2);
    return false;
}
