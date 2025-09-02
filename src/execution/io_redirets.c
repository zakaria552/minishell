#include "minishell.h"

static void	redirect_stdin(t_cmd *cmd, char *file);
static void	redirect_stdout(t_cmd *cmd, t_token *redirect);
static void	redirect_here_doc(t_cmd *cmd);
static void	pipe_redirect(t_cmd *cmd);

void	redirect_io(t_cmd *cmd, bool redir_pipeline)
{
	t_vector		*redirects;
	t_token			*redir;
	t_token_type	type;
	int				i;

	redirects = cmd->redirects;
	get_local_vars()->io_err = false;
	i = -1;
	if (redir_pipeline)
		pipe_redirect(cmd);
	while (++i < redirects->size)
	{
		redir = (t_token *)redirects->get(redirects, i);
		type = redir->type;
		if (!redir_pipeline && get_local_vars()->io_err)
			break;
		if (type == INPUT_REDIR)
			redirect_stdin(cmd, redir->content);
		else if (type == OUTPUT_REDIR || type == OUTPUT_APPEND)
			redirect_stdout(cmd, redir);
	}
	redirect_here_doc(cmd);
	if (get_local_vars()->io_err)
		set_status(1);
}

static void	redirect_stdin(t_cmd *cmd, char *file)
{
	const int	fd = open(file, O_RDONLY);

	if (fd < 0)
	{
		get_local_vars()->io_err = true;
		return runtime_err(1, file);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		get_local_vars()->io_err = true;
		if (cmd->fd_here_doc > 0)
			close(cmd->fd_here_doc);
		close(fd);
		return runtime_err(errno, NULL);
	}
	close(fd);
}

static void	redirect_stdout(t_cmd *cmd, t_token *redirect)
{
	int	fd;
	int	flags;

	flags = O_RDWR | O_CREAT;
	if (redirect->type == OUTPUT_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(redirect->content, flags, 0644);
	if (fd < 0)
	{
		get_local_vars()->io_err = true;
		if (cmd->fd_here_doc > 0)
			close(cmd->fd_here_doc);
		return runtime_err(1, redirect->content);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		get_local_vars()->io_err = true;
		if (cmd->fd_here_doc > 0)
			close(cmd->fd_here_doc);
		close(fd);
		return runtime_err(errno, NULL);
	}
	close(fd);
}

static void	redirect_here_doc(t_cmd *cmd)
{
	t_token		*last_redirect;
	const int	fd = cmd->fd_here_doc;

	if (cmd->redirects->size == 0 || fd < 0)
		return ;
	last_redirect = (t_token *)cmd->redirects->get(cmd->redirects,
			cmd->redirects->size - 1);
	if (last_redirect->type != HERE_DOC)
	{
		close(fd);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		get_local_vars()->io_err = true;
		close(fd);
		return runtime_err(errno, NULL);
	}
	close(fd);
}

static void	pipe_redirect(t_cmd *cmd)
{
	if ((!cmd->is_first_cmd && dup2(cmd->curr_pipe[0], STDIN_FILENO) < 0)
		|| (!cmd->is_last_cmd && dup2(cmd->next_pipe[1], STDOUT_FILENO) < 0))
	{
		close_pipe(cmd->curr_pipe);
		close_pipe(cmd->next_pipe);
		if (cmd->fd_here_doc > 0)
			close(cmd->fd_here_doc);
		runtime_err(errno, NULL);
	}
	close_pipe(cmd->curr_pipe);
	close_pipe(cmd->next_pipe);
}
