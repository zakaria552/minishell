#include "minishell.h"

static bool	should_remove_line(char *flag);
static void	echo_args(t_cmd *cmd, bool remove_line);

void	echo(t_cmd *cmd)
{
	bool	remove_line;
	char	*arg;

	if (cmd->args->size == 0)
	{
		ft_printf("\n");
		return ;
	}
	arg = cmd->args->get(cmd->args, 0);
	remove_line = should_remove_line(arg);
	echo_args(cmd, remove_line);
	set_status(0);
}

static bool	should_remove_line(char *flag)
{
	bool	remove;
	int		i;

	if (flag[0] != '-')
		return (false);
	if (!flag[1] || flag[1] != 'n')
		return (false);
	remove = true;
	i = 1;
	while (flag[i])
	{
		if (flag[i] != 'n')
		{
			remove = false;
			break ;
		}
		i++;
	}
	return (remove);
}

static void	echo_args(t_cmd *cmd, bool remove_line)
{
	char	*arg;
	int		i;

	i = 0;
	if (remove_line)
		i++;
	while (remove_line && i < cmd->args->size)	
	{
		arg = cmd->args->get(cmd->args, i);
		if (!should_remove_line(arg))
			break;
		i++;
	}
	while (i < cmd->args->size)
	{
		arg = cmd->args->get(cmd->args, i);
		ft_printf("%s", arg);
		if (i != cmd->args->size - 1)
			ft_printf(" ");
		i++;
	}
	if (!remove_line)
		ft_printf("\n");
}
