#include "minishell.h"

volatile sig_atomic_t	g_signal;

int	main(int argc, char **args, char **envp)
{
	int	status;

	(void)argc;
	(void)args;
	init_local_vars(envp);
	launch_shell();
	status = get_local_vars()->status;
	clean_up(true, true);
	return (status);
}
