#include "minishell.h"

static void	non_numeric_err_msg(t_cmd *cmd);
static int	get_exit_status(t_cmd *cmd, bool *should_exit);

void	builtin_exit(t_cmd *cmd, bool *should_exit)
{
	t_local_vars	*vars;

	vars = get_local_vars();
	*should_exit = true;
	if (cmd->args->size == 0)
	{
		// ft_printf("exit\n");
		return ;
	}
	if (cmd->args)
		vars->status = get_exit_status(cmd, should_exit);
}

static void	non_numeric_err_msg(t_cmd *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args->get(cmd->args, 0), 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static int	get_exit_status(t_cmd *cmd, bool *should_exit)
{
	long		num;
	bool		error;
	const char	*arg1 = cmd->args->get(cmd->args, 0);

	error = false;
	num = long_atoi((char *)arg1, &error);
	if (error || !*arg1)
	{
		// ft_printf("exit\n");
		non_numeric_err_msg(cmd);
		return (2);
	}
	if (cmd->args->size > 1)
	{
		*should_exit = false;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	// ft_printf("exit\n");
	return (num % 256);
}
