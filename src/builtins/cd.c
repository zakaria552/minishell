#include "minishell.h"

static void	invalid_directory_msg(char *arg, char *msg)
{
	t_local_vars	*vars;

	vars = get_local_vars();
	vars->status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" :", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	set_status(1);
}

static void	change_directory(char *path)
{
	t_local_vars		*vars;
	const t_allocators	*allocs = get_allocators();
	int					temp;

	vars = get_local_vars();
	temp = chdir(path);
	if (temp == -1)
		invalid_directory_msg(path, "Couldn't access directory");
	else
	{
		vars->pwd = pwd_to_string(allocs->global);
		vars->set(arena_strjoin(allocs->global, "PWD=", vars->pwd));
		set_status(0);
	}
}

void	cd(t_cmd *cmd)
{
	struct stat	directory;
	char		*arg;
	int			test;

	if (cmd->args->size == 0 || cmd->args->size > 1)
	{
		if (cmd->args->size > 1)
			invalid_directory_msg(NULL, "too many arguments");
		return ;
	}
	arg = (char *)cmd->args->get(cmd->args, 0);
	test = stat(arg, &directory);
	if (test == -1)
		invalid_directory_msg(arg, "no such file or directory");
	else
	{
		if (S_ISDIR(directory.st_mode))
			change_directory(arg);
		else
			invalid_directory_msg(arg, "not a directory");
	}
}
