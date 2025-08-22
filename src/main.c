#include "minishell.h"
volatile sig_atomic_t	g_signal;

int main(int argc, char **args, char **envp)
{
	(void)argc;
	(void)args;

	init_local_vars(envp);
	launch_shell();
	return (get_local_vars()->status);
}
