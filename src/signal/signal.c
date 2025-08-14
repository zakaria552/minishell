/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:52:25 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/15 14:09:51 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

volatile sig_atomic_t	g_signal;

void	set_readline_handler(void)
{
	struct sigaction	s_sig;

	g_signal = 0;
	s_sig.sa_sigaction = handler;
	sigemptyset(&s_sig.sa_mask);
	s_sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &s_sig, NULL) == -1)
		exit(1);
}

void	set_here_doc_handler(void)
{
	struct sigaction	s_sig;

	g_signal = 0;
	s_sig.sa_sigaction = here_doc_handler;
	sigemptyset(&s_sig.sa_mask);
	s_sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &s_sig, NULL) == -1)
		exit(1);
}

//handler for when in readline mode:
//moves to a new line, empties readline buffer with rl_replace_line (1 tells it 
//to also empty undo list, which I don't think we're using, so 0 would work 
//the same), then tells readline that it should treat it as having a completed 
//line, and to redisplay the prompt
void	handler(int signum, siginfo_t *act, void *next)
{
	(void)next;
	(void)act;
	g_signal = signum;
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	here_doc_handler(int signum, siginfo_t *act, void *next)
{
	(void)next;
	(void)act;
	g_signal = signum;
}
