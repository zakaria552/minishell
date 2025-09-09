/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:20 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/09 17:10:25 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_cmd_here_doc(t_arena *arena, t_cmd *cmd, char *limiter);
static char	*alt_strip_quotes(t_arena *arena, char *str);
static void	clean_up_here_doc(t_cmd *cmd, char *file, char *line);
static bool	should_expand(char *delimiter);

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
			if (g_signal)
				return ;
		}
	}
}

static void	clean_up_here_doc(t_cmd *cmd, char *file, char *line)
{
	t_local_vars	*vars;

	vars = get_local_vars();
	if (g_signal)
		vars->status = 128 + g_signal;
	else
	{
		if (!line)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		if (cmd->fd_here_doc > 0)
			close(cmd->fd_here_doc);
		cmd->fd_here_doc = open(file, O_RDWR);
		if (cmd->fd_here_doc < 0)
			shell_err(file);
	}
}

static void	set_cmd_here_doc(t_arena *arena, t_cmd *cmd, char *limiter)
{
	const bool	expand = should_expand(limiter);
	const char *file = here_doc_file();
	int fd;
	char		*line;

	limiter = alt_strip_quotes(arena, limiter);
	fd = open((char *)file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		shell_err((char *)file);
		return;
	}
	set_here_doc_handler();
	while (g_signal == 0)
	{
		line = int_tty_prompt(PROMPT_HEREDOC_MSG, false, isatty(STDIN_FILENO));
		if (!line || strmatch(line, limiter))
			break ;
		if (expand)
			line = alt_expand_str(arena, line);
		if (write(fd, line, ft_strlen(line)) < 0 || write(fd, "\n", 1) < 0)
			runtime_err(errno, NULL);
	}
	close(fd);
	clean_up_here_doc(cmd, (char *)file, line);
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

static bool	should_expand(char *delimiter)
{
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
		return (false);
	return (true);
}
