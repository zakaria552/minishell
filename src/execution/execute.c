/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:18 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/15 11:04:35 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(t_vector *cmds, int index, t_arena *arena);
static char	**execve_args(t_arena *arena, t_cmd *cmd, char *binary);
static void	pipeline(t_vector *cmds, t_arena *arena);
static void	wait_child_processes(t_vector *cmds);

void	execute_commands(t_vector *cmds, t_arena *arena)
{
	t_local_vars	*vars;

	vars = get_local_vars();
	vars->pipeline = !(cmds->size == 1 && is_builtin(((t_cmd *)cmds->get(cmds,
						0))->cmd));
	if (!vars->pipeline && (g_signal == 0))
		execute_builtin(cmds, 0, false);
	if (vars->pipeline && (g_signal == 0))
	{
		set_handler_to_ignore();
		pipeline(cmds, arena);
	}
	close_open_here_docs(cmds, -1);
	if (vars->pipeline && (g_signal == 0))
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
	set_handler_to_default();
	close_open_here_docs((t_vector *)cmds, index);
	redirect_io((t_cmd *)cmd, true);
	if (!cmd->cmd)
		clean_up_and_exit(0);
	execute_builtin(cmds, index, true);
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
	bool			signalled;

	i = -1;
	vars = get_local_vars();
	signalled = false;
	while (++i < cmds->size)
	{
		cmd = ((t_cmd *)cmds->get(cmds, i));
		waitpid(cmd->pid, &status, 0);
		if (WIFSIGNALED(status))
			handle_child_signal(&signalled, status);
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
