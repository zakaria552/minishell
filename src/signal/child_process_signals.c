/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:56 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/15 11:04:47 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_signal(bool *signalled, int status)
{
	if (WTERMSIG(status) == SIGQUIT && !*signalled)
		reset_readline("Quit. Core dumped", SIGQUIT);
	else if (WTERMSIG(status) == SIGINT && !*signalled)
		reset_readline("", SIGINT);
	*signalled = true;
	set_handler_to_ignore();
}
