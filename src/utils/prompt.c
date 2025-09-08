/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:31:17 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/06 18:45:56 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_prompt(char *prompt_msg, bool update_history);
static void	display_working_dir(void);

char	*int_tty_prompt(char *prompt_msg, bool update_history, bool interactive)
{
	t_allocators	*allocs;
	char			*prompt;
	char			*arena_prompt;
	char			*line;

	allocs = get_allocators();
	if (interactive)
		return (read_prompt(prompt_msg, update_history));
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	prompt = ft_strtrim(line, "\n");
	if (!prompt)
	{
		free(line);
		return (NULL);
	}
	free(line);
	arena_prompt = arena_strdup(allocs->prompt, prompt);
	free(prompt);
	return (arena_prompt);
}

static char	*read_prompt(char *prompt_msg, bool update_history)
{
	t_allocators	*allocs;
	char			*prompt;
	char			*arena_prompt;

	(void)prompt_msg;
	allocs = get_allocators();
	if (update_history)
		display_working_dir();
	prompt = readline(prompt_msg);
	if (!prompt)
	{
		if (errno > 0)
			runtime_err(errno, NULL);
		return (NULL);
	}
	arena_prompt = arena_alloc(allocs->prompt, ft_strlen(prompt) + 1, prompt);
	free(prompt);
	if (update_history)
		add_history(arena_prompt);
	return (arena_prompt);
}

static void	display_working_dir(void)
{
	char	*pwd;
	char	*working_dir;
	char	*tmp;

	pwd = pwd_to_string(get_allocators()->prompt);
	working_dir = ft_strrchr(pwd, '/');
	if (!working_dir)
	{
		ft_printf(PROMPT_PWD, pwd);
		return ;
	}
	tmp = working_dir;
	working_dir++;
	*tmp = '\0';
	ft_printf(PROMPT_HOME, pwd);
	ft_printf(PROMPT_CURRENT_DIR, working_dir);
}

void	border_message(void)
{
	if (!isatty(STDIN_FILENO))
		return ;
	ft_printf(MINISHELL_ASCII_TITLE);
	ft_printf(MINISHELL_BORDER_MSG, ttyname(STDIN_FILENO));
}
