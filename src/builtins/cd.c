#include "minishell.h"

int	cd(t_cmd *cmd)
{
	struct stat		directory;
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
	test = stat(cmd->args->get(cmd->args, 0), &directory);
	if (test)
		runtime_err(errno, "cd :");
	else
	{
		if (S_ISDIR(directory.st_mode)
			change_directory(path);
		else
			runtime_err(errno, "cd :");
	}
	return (0);
}
