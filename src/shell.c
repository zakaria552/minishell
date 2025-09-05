/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:31:29 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:31:30 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_shell(void)
{
	t_allocators	*allocs;
	t_vector		*commands;
	char			*prompt;

	allocs = get_allocators();
	border_message();
	while (true)
	{
		allocs->prompt = init_arena(ARENA_SIZE);
		set_readline_handler();
		prompt = int_tty_prompt(PROMPT_MSG, true, isatty(STDIN_FILENO));
		if (!prompt)
			break ;
		commands = tokenize_and_parse(prompt, allocs->prompt, '\0');
		if (!commands)
		{
			clean_up(false, false);
			continue ;
		}
		handle_here_doc(commands);
		execute_commands(commands, allocs->prompt);
		clean_up(false, false);
	}
}

t_allocators	*get_allocators(void)
{
	static t_allocators	arenas;

	if (!arenas.global)
		arenas.global = init_arena(ARENA_SIZE);
	return (&arenas);
}
