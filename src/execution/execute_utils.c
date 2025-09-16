/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:15 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/15 14:04:44 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	update_cmd_pipes(t_cmd *cmd, int *curr_pipe, int *next_pipe)
{
	ft_memcpy(cmd->curr_pipe, curr_pipe, sizeof(curr_pipe));
	ft_memcpy(cmd->next_pipe, next_pipe, sizeof(next_pipe));
}

void	init_pipes(int *curr, int *next)
{
	curr[0] = -1;
	curr[1] = -1;
	next[0] = -1;
	next[1] = -1;
}
