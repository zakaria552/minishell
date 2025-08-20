#include "minishell.h"

static void    non_numeric_err_msg(t_cmd *cmd);
static int	long_atoi(const char *nptr, bool *error);

void    builtin_exit(t_cmd *cmd, bool *should_exit)
{
    t_local_vars *vars;
    long num;
    bool error;

    vars = get_local_vars();
    error = false;
    *should_exit = true;
    if (cmd->args->size == 0)
        return;
    if (cmd->args->size > 1)
    {
        vars->status = 1;
        *should_exit = false;
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return;
    }
    num = long_atoi(cmd->args->get(cmd->args, 0), &error);
    if (!error)
        vars->status = num % 256;
    else
    {
        non_numeric_err_msg(cmd);
        vars->status = 2;
    }
}

static void    non_numeric_err_msg(t_cmd *cmd)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(cmd->args->get(cmd->args, 0), 2);
    ft_putstr_fd(": numeric argument required\n", 2);
}

static int	long_atoi(const char *nptr, bool *error)
{
	long long	num;
	int	    i;
	int	    sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (nptr[i] && nptr[i] <= '9' && nptr[i] >= '0')
	{
        if (((num * 10) + (nptr[i] - '0')) < num)
            break;
		num = num * 10 + nptr[i] - '0';
		i++;
	}
    if (nptr[i])
        *error = true;
    return (num * sign);
}
