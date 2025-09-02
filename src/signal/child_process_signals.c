#include "minishell.h"

void    handle_child_signal(t_local_vars *vars, bool *signalled, int status)
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
