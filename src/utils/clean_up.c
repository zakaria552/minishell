/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:08:07 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/15 14:05:09 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up(bool clean_global, bool clean_history)
{
	t_allocators	*allocs;

	allocs = get_allocators();
	if (allocs->global && clean_global)
	{
		allocs->global->destroy(allocs->global);
		allocs->global = NULL;
	}
	if (allocs->prompt)
	{
		allocs->prompt->destroy(allocs->prompt);
		allocs->prompt = NULL;
	}
	if (clean_history)
		clear_history();
}

void	clean_up_and_exit(int err_code)
{
	clean_up(true, true);
	exit(err_code);
}

void	clean_runtime_err(int err_code, char *msg, int *curr_pipe,
		int *next_pipe)
{
	ft_putstr_fd("minishell: ", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(":", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (!get_local_vars()->pipeline)
		return ;
	if (curr_pipe[0] != -1)
		close_pipe(curr_pipe);
	if (next_pipe[0] != -1)
		close_pipe(next_pipe);
	clean_up(true, true);
	exit(err_code);
}
