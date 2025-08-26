#include "minishell.h"

static void	exc_builtin(t_cmd *cmd, t_local_vars *vars, bool *should_exit);

void	execute_builtin(t_vector *cmds, int index, bool should_exit)
{
	const t_cmd		*cmd = cmds->get(cmds, index);
	t_local_vars	*vars;

	vars = get_local_vars();
	if (!is_builtin(cmd->cmd))
		return ;
	vars->stdin_cpy = dup(STDIN_FILENO);
	vars->stdout_cpy = dup(STDOUT_FILENO);
	if (vars->stdin_cpy < 0)
		runtime_err(errno, NULL);
	if (vars->stdout_cpy < 0)
	{
		close(vars->stdin_cpy);
		runtime_err(errno, NULL);
	}
	if (!vars->pipeline)
		redirect_io((t_cmd *)cmd, false);
	exc_builtin((t_cmd *)cmd, vars, &should_exit);
	if (should_exit || vars->pipeline)
	{
		close_open_here_docs(cmds, -1);
		clean_up(true, true);
		exit(vars->status);
	}
}

static void	exc_builtin(t_cmd *cmd, t_local_vars *vars, bool *should_exit)
{
	if (!vars->io_err && strmatch(cmd->cmd, "export"))
		export((t_cmd *)cmd);
	else if (!vars->io_err && strmatch(cmd->cmd, "unset"))
		unset((t_cmd *)cmd);
	else if (!vars->io_err && strmatch(cmd->cmd, "env"))
		env();
	else if (!vars->io_err && strmatch(cmd->cmd, "exit"))
		builtin_exit((t_cmd *)cmd, should_exit);
	else if (!vars->io_err && strmatch(cmd->cmd, "echo"))
		echo(cmd);
	else if (!vars->io_err && strmatch(cmd->cmd, "cd"))
		cd(cmd);
	else if (!vars->io_err && strmatch(cmd->cmd, "pwd"))
		pwd();
	if (dup2(vars->stdin_cpy, STDIN_FILENO) < 0 || dup2(vars->stdout_cpy,
			STDOUT_FILENO) < 0)
	{
		close(vars->stdin_cpy);
		close(vars->stdout_cpy);
		return runtime_err(errno, NULL);
	}
	close(vars->stdin_cpy);
	close(vars->stdout_cpy);
}

char	**envp_vars(void)
{
	const t_local_vars	*vars = get_local_vars();
	const size_t		size = sizeof(char *) * (vars->envp->size + 1);
	t_env_var			*var;
	char				**envp;
	int					i;

	i = -1;
	envp = get_allocators()->prompt->alloc(get_allocators()->prompt, size,
			NULL);
	while (++i < vars->envp->size)
	{
		var = vars->envp->get(vars->envp, i);
		envp[i] = var->joint;
	}
	envp[i] = NULL;
	return (envp);
}
