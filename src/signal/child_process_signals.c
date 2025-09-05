/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:56 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:30:57 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_signal(t_local_vars *vars, bool *signalled, int status)
{
	if (WTERMSIG(status) == SIGQUIT && !*signalled)
		reset_readline("Quit. Core dumped", SIGQUIT);
	else if (WTERMSIG(status) == SIGINT && !*signalled)
		reset_readline("", SIGINT);
	else
		vars->status = WEXITSTATUS(status);
	*signalled = true;
	set_handler_to_ignore();
}
