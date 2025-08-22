#include "minishell.h"

static void set_cmd_here_doc(t_cmd *cmd, char *limiter);
// static bool    should_expand(char *line);

void    handle_here_doc(t_vector *cmds)
{
    t_cmd *cmd;
    t_token *token;
    int i;
    int j;

    i = -1;
    while (++i < cmds->size)
    {
        cmd = (t_cmd *)(cmds->get(cmds, i));
        j = -1;
        cmd->fd_here_doc = -1;
        cmd->is_first_cmd = i == 0;
        cmd->is_last_cmd = i == cmds->size - 1;
        while (++j < cmd->redirects->size)
        {
            token = (t_token *)cmd->redirects->get(cmd->redirects, j);
            if (token->type != HERE_DOC)
                continue;
            set_cmd_here_doc(cmd, token->content);
        }
    }
}

static void exit_after_signal(int *hdoc_pipe)
{
	t_local_vars *vars = get_local_vars();

	vars->status = 128 + g_signal;
	close_pipe(hdoc_pipe);
}

static void set_cmd_here_doc(t_cmd *cmd, char *limiter)
{
    const t_arena *arena = get_allocators()->prompt;
    const bool expand = true;
    int hdoc_pipe[2];
    char *line;
    char *expanded;
	if (pipe(hdoc_pipe) < 0)
		runtime_err(errno, NULL);
	set_here_doc_handler();
    while (g_signal == 0)
    {
        line = int_tty_prompt(">", false, isatty(STDIN_FILENO));
        expanded = line;
		if (!line)
			break ;
        if (expand)
            expanded = expand_str(line, (t_arena *)arena);
        if (strmatch(line, limiter))
			break ;
        if (write(hdoc_pipe[1], expanded, ft_strlen(expanded)) < 0 || write(hdoc_pipe[1], "\n", 1) < 0)
            runtime_err(errno, NULL); 
    }
	if (g_signal)
		exit_after_signal(hdoc_pipe);
	else
	{
		if (!line)
		{
			rl_replace_line("", 1);
			rl_on_new_line();
		}
		close(cmd->fd_here_doc);
		cmd->fd_here_doc = hdoc_pipe[0];
		close(hdoc_pipe[1]);
	}
}

void    close_open_here_docs(t_vector *cmds, int index)
{
    t_cmd *cmd;
    int i;

    i = -1;
    while (++i < cmds->size)
    {
        cmd = (t_cmd *)(cmds->get(cmds, i));
        if (cmd->fd_here_doc > 0 && i != index)
        {
            close(cmd->fd_here_doc);
            cmd->fd_here_doc = -1;
        }
    }
}

// static bool    should_expand(char *delimiter)
// {
//     const int len = ft_strlen(delimiter);

//     if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'') ||
//         (delimiter[0] == '\"' && delimiter[len - 1] == '\"'))
//         return false;
//     return true;
// }