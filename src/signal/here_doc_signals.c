/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:59 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:31:00 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_readline_flagger(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

//Here_doc behaviour: Ctrl-C interrupts, Ctrl-\ is ignored
void	set_here_doc_handler(void)
{
	struct sigaction	s_heredoc;
	struct sigaction	s_ignore;

	g_signal = 0;
	rl_done = 0;
	rl_event_hook = here_doc_readline_flagger;
	ft_memset(&s_heredoc, 0, sizeof(s_heredoc));
	ft_memset(&s_ignore, 0, sizeof(s_ignore));
	s_heredoc.sa_sigaction = here_doc_signal_handler;
	s_heredoc.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &s_heredoc, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	s_ignore.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &s_ignore, NULL) == -1)
		runtime_err(errno, "registering signal handler");
}

void	here_doc_signal_handler(int signum, siginfo_t *act, void *next)
{
	(void)next;
	(void)act;
	g_signal = signum;
}
