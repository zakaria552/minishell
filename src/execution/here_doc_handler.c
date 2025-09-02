#include "minishell.h"

static void	set_cmd_here_doc(t_arena *arena, t_cmd *cmd, char *limiter);
static bool	should_expand(char *line);
//static char* strip_quotes3(char *str);
static char	*alt_strip_quotes(t_arena *arena, char *str);

void	handle_here_doc(t_vector *cmds)
{
	t_arena	*arena;
	t_cmd	*cmd;
	t_token	*token;
	int		i;
	int		j;

	arena = get_allocators()->prompt;
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
				continue ;
			set_cmd_here_doc(arena, cmd, token->content);
		}
	}
}

static void	clean_up_here_doc(t_cmd *cmd, int *hdoc_pipe, char *line)
{
	t_local_vars	*vars;

	vars = get_local_vars();
	if (g_signal)
	{
		vars->status = 128 + g_signal;
		close_pipe(hdoc_pipe);
	}
	else
	{
		if (!line)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		close(cmd->fd_here_doc);
		cmd->fd_here_doc = hdoc_pipe[0];
		close(hdoc_pipe[1]);
	}
}

static void	set_cmd_here_doc(t_arena *arena, t_cmd *cmd, char *limiter)
{
	const bool	expand = should_expand(limiter);
	int			hdoc_pipe[2];
	char		*line;

	limiter = alt_strip_quotes(arena, limiter);
	if (pipe(hdoc_pipe) < 0)
		runtime_err(errno, NULL);
	set_here_doc_handler();
	while (g_signal == 0)
	{
		line = int_tty_prompt(PROMPT_HEREDOC_MSG, false, isatty(STDIN_FILENO));
		if (!line || strmatch(line, limiter))
			break ;
		if (expand)
			line = alt_expand_str(arena, line);
		if (write(hdoc_pipe[1], line, ft_strlen(line)) < 0 \
|| write(hdoc_pipe[1], "\n", 1) < 0)
			runtime_err(errno, NULL);
	}
	clean_up_here_doc(cmd, hdoc_pipe, line);
}

static char	*alt_strip_quotes(t_arena *arena, char *str)
{
	t_vector	*vec;
	t_token		*tok;
	char		*limiter;
	int			i;

	vec = tokenize_input(str, arena, '\0');
	i = -1;
	limiter = arena_strdup(arena, "");
	while (++i < vec->size)
	{
		tok = vec->get(vec, i);
		if (tok->type == QUOTE_SINGLE || tok->type == QUOTE_DOUBLE)
			limiter = arena_strjoin(arena, limiter, strip_quotes(arena, \
tok->content, true));
		else
			limiter = arena_strjoin(arena, limiter, tok->content);
	}
	return (limiter);
}

void	close_open_here_docs(t_vector *cmds, int index)
{
	t_cmd	*cmd;
	int		i;

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

static bool	should_expand(char *delimiter)
{
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
		return (false);
	return (true);
}
/*
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
*/
