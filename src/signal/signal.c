/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:31:02 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:31:03 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_readline(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line(PROMPT_MSG, 0);
	set_status(status + 128);
	set_handler_to_ignore();
}

//Ctrl-C handled by handler, ctrl-\ ignored
//resets rl globals
void	set_readline_handler(void)
{
	struct sigaction	s_signal;
	struct sigaction	s_ignore;

	g_signal = 0;
	rl_done = 0;
	rl_event_hook = NULL;
	ft_memset(&s_signal, 0, sizeof(s_signal));
	ft_memset(&s_ignore, 0, sizeof(s_ignore));
	s_signal.sa_sigaction = signal_handler;
	s_signal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	s_ignore.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &s_ignore, NULL) == -1)
		runtime_err(errno, "registering signal handler");
}

void	set_handler_to_default(void)
{
	struct sigaction	s_signal;

	g_signal = 0;
	rl_event_hook = NULL;
	ft_memset(&s_signal, 0, sizeof(s_signal));
	s_signal.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	if (sigaction(SIGQUIT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
}

void	set_handler_to_ignore(void)
{
	struct sigaction	s_ignore;

	g_signal = 0;
	rl_event_hook = NULL;
	ft_memset(&s_ignore, 0, sizeof(s_ignore));
	s_ignore.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &s_ignore, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	if (sigaction(SIGQUIT, &s_ignore, NULL) == -1)
		runtime_err(errno, "registering signal handler");
}

//handler for when in readline mode:
//moves to a new line, empties readline buffer with rl_replace_line (1 tells it 
//to also empty undo list, which I don't think we're using, so 0 would work 
//the same), then tells readline that it should treat it as having a completed 
//line, and to redisplay the prompt
void	signal_handler(int signum, siginfo_t *act, void *next)
{
	(void)next;
	(void)act;
	if (signum == SIGINT)
	{
		set_status(128 + signum);
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
