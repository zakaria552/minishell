#include "minishell.h"

int	cd(t_cmd *cmd)
{
	struct stat		buf;
	t_local_vars	*vars;
	int				test;
	
	vars = get_local_vars();
	if (cmd->args->size == 0)
		return (0);
	if (cmd->args->size > 1)
	{
		vars->status = 1;
		return (1);
	}
	test = stat(cmd->args->get(cmd->args, 0), &buf);
	if (test)
		runtime_err(errno, "cd :");
	else
	{
		if (chdir(cmd->args->get(cmd->args, 0)) == -1)
			runtime_err(errno, "cd :");
	}
	return (0);
}
