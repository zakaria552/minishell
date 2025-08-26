#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

void	reset_readline(char *msg, int status);
void	set_readline_handler(void);
void	set_here_doc_handler(void);
void	signal_handler(int signum, siginfo_t *act, void *next);
void	here_doc_signal_handler(int signum, siginfo_t *act, void *next);
int 	here_doc_readline_flagger(void);
void	set_handler_to_default(void);
void	set_handler_to_ignore(void);

# include <signal.h>
# include <sys/types.h>

extern volatile sig_atomic_t	g_handler_flag;

#endif
