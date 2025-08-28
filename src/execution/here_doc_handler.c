#include "minishell.h"

static void set_cmd_here_doc(t_cmd *cmd, char *limiter);
static bool    should_expand(char *line);
static char* strip_quotes3(char *str);

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
    const bool expand = should_expand(limiter);
    int hdoc_pipe[2];
    char *line;

    limiter = strip_quotes3(limiter);
	if (pipe(hdoc_pipe) < 0)
		runtime_err(errno, NULL);
	set_here_doc_handler();
    while (g_signal == 0)
    {
        line = int_tty_prompt(PROMPT_HEREDOC_MSG, false, isatty(STDIN_FILENO));
		if (!line)
			break ;
        if (expand)
            line = expand_str(line, (t_arena *)arena);
        if (strmatch(line, limiter))
			break ;
        if (write(hdoc_pipe[1], line, ft_strlen(line)) < 0 || write(hdoc_pipe[1], "\n", 1) < 0)
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

char	*alt_strip_quotes(t_arena *arena, char *str)
{
	t_vector	vec;
	char		*limiter;

	vec = tokenize_input(arena, str, '\0');
	
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

static bool    should_expand(char *delimiter)
{
    if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
        return false;
    return true;
}

static char * strip_quotes3(char *str)
{
    char *read;
    char *write;
    bool  quoted = {0};
    char type = '\0';
    const int len = ft_strlen(str);

    read = str;
    write = str;
    if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len - 1] == '\"'))
    {
        str[len - 1] = '\0';
        str++;
        return str;
    }
    while (read && *read)
    {
        if (!quoted && (*read == '\'' || *read == '\"'))
        {
            quoted = true;
            type = *read;
        }
        while (quoted)
        {
            if (*read == type)
            {
                quoted = false;
                read++;
            }
            read++;
        }
        if (!quoted)
        {
            *write = *read;
            write++;
        }
        if (*read)
          read++;
    }
    *write = *read;
    return str;
}
