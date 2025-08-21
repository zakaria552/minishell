#include "minishell.h"

int here_doc_readline_flagger(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

//Ctrl-C handled by handler, ctrl-\ ignored
//reset rl globals
void	set_readline_handler(void)
{
	struct sigaction	s_signal;
	struct sigaction	s_ignore;

	g_signal = 0;
	rl_done = 0;
	rl_event_hook = NULL;
	s_signal.sa_sigaction = signal_handler;
	sigemptyset(&s_signal.sa_mask);
	s_signal.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	s_ignore.sa_handler = SIG_IGN;
	sigemptyset(&s_ignore.sa_mask);
	if (sigaction(SIGQUIT, &s_ignore, NULL) == -1)
		runtime_err(errno, "registering signal handler");
}

void	set_handler_to_default(void)
{
	struct sigaction	s_signal;
	
	g_signal = 0;
	rl_event_hook = NULL;
	s_signal.sa_handler = SIG_DFL;
	sigemptyset(&s_signal.sa_mask);
	if (sigaction(SIGINT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	if (sigaction(SIGQUIT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
}

void	set_handler_to_ignore(void)
{
	struct sigaction	s_signal;
	
	g_signal = 0;
	rl_event_hook = NULL;
	s_signal.sa_handler = SIG_IGN;
	sigemptyset(&s_signal.sa_mask);
	if (sigaction(SIGINT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	if (sigaction(SIGQUIT, &s_signal, NULL) == -1)
		runtime_err(errno, "registering signal handler");
}

//Here_doc behaviour: Ctrl-C interrupts, Ctrl-\ is ignored
void	set_here_doc_handler(void)
{
	struct sigaction	s_heredoc;
	struct sigaction	s_ignore;

	g_signal = 0;
	rl_done = 0;
	rl_event_hook = here_doc_readline_flagger;
	s_heredoc.sa_sigaction = here_doc_signal_handler;
	sigemptyset(&s_heredoc.sa_mask);
	s_heredoc.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &s_heredoc, NULL) == -1)
		runtime_err(errno, "registering signal handler");
	s_ignore.sa_handler = SIG_IGN;
	sigemptyset(&s_ignore.sa_mask);
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
	g_signal = 128 + signum;
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

void	here_doc_signal_handler(int signum, siginfo_t *act, void *next)
{
	(void)next;
	(void)act;
	g_signal = signum;
}
