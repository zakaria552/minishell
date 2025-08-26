#include "minishell.h"

static void	execute_cmd(t_vector *cmds, int index, t_arena *arena);
static char	**execve_args(t_arena *arena, t_cmd *cmd, char *binary);
static void	pipeline(t_vector *cmds, t_arena *arena);
static void	wait_child_processes(t_vector *cmds);

void	execute_commands(t_vector *cmds, t_arena *arena)
{
	bool	is_single_builtin;

	is_single_builtin = cmds->size == 1 && is_builtin(((t_cmd *)cmds->get(cmds,
					0))->cmd);
	if (is_single_builtin && (g_signal == 0))
		execute_builtin(cmds, 0, false, false);
	if (!is_single_builtin && (g_signal == 0))
	{
		set_handler_to_default();
		pipeline(cmds, arena);
	}
	close_open_here_docs(cmds, -1);
	if (!is_single_builtin && (g_signal == 0))
		wait_child_processes(cmds);
	set_readline_handler();
}

static void	pipeline(t_vector *cmds, t_arena *arena)
{
	t_cmd	*cmd;
	int		curr_pipe[2];
	int		next_pipe[2];
	int		i;

	i = -1;
	if (pipe(curr_pipe) < 0)
		runtime_err(errno, NULL);
	while (++i < cmds->size)
	{
		cmd = ((t_cmd *)cmds->get(cmds, i));
		if (!cmd->cmd)
			continue ;
		if (pipe(next_pipe) < 0)
			runtime_err(errno, NULL);
		update_cmd_pipes(cmd, curr_pipe, next_pipe);
		cmd->pid = fork();
		if (cmd->pid < 0)
			runtime_err(errno, NULL);
		if (cmd->pid == 0)
			execute_cmd(cmds, i, arena);
		close_pipe(curr_pipe);
		ft_memcpy(curr_pipe, next_pipe, sizeof(curr_pipe));
	}
	close_pipe(curr_pipe);
}

static void	execute_cmd(t_vector *cmds, int index, t_arena *arena)
{
	const t_cmd	*cmd = cmds->get(cmds, index);
	char		**envp;
	char		*path;
	char		**args;

	envp = envp_vars();
	set_handler_to_ignore();
	close_open_here_docs((t_vector *)cmds, index);
	redirect_io((t_cmd *)cmd, true);
	execute_builtin(cmds, index, true, true);
	path = get_binary_path(cmd->cmd, envp, arena);
	args = execve_args(arena, (t_cmd *)cmd, path);
	execve(path, args, envp);
	set_handler_to_ignore();
	runtime_err(errno, NULL);
}

static void	wait_child_processes(t_vector *cmds)
{
	t_local_vars	*vars;
	t_cmd			*cmd;
	int				status;
	int				i;

	i = -1;
	vars = get_local_vars();
	while (++i < cmds->size)
	{
		cmd = ((t_cmd *)cmds->get(cmds, i));
		waitpid(cmd->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				reset_readline("Quit. Core dumped", SIGQUIT);
			else if (WTERMSIG(status) == SIGINT)
				reset_readline("", SIGINT);
			else
				vars->status = WEXITSTATUS(status);
			set_handler_to_ignore();
		}
		else
			vars->status = WEXITSTATUS(status);
	}
}

static char	**execve_args(t_arena *arena, t_cmd *cmd, char *binary)
{
	t_vector	*cmd_args;
	char		**args;
	int			i;

	cmd_args = cmd->args;
	args = arena->alloc(arena, sizeof(char *) * (cmd_args->size + 2), NULL);
	args[0] = binary;
	i = -1;
	while (++i < cmd_args->size)
		args[i + 1] = cmd_args->get(cmd_args, i);
	args[i + 1] = NULL;
	return (args);
}
