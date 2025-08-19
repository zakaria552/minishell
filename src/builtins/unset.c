#include "minishell.h"

void    unset(t_cmd *cmd)
{
    t_local_vars *vars;
    int i;

    i = -1;
    vars = get_local_vars();
    while (++i < cmd->args->size)
        vars->unset(cmd->args->get(cmd->args, i));
    vars->status = 0;
}
