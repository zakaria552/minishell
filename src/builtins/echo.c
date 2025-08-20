#include "minishell.h"

static bool    should_remove_line(char *flag);

void    echo(t_cmd *cmd)
{
    const t_local_vars *vars = get_local_vars();
    bool    remove_line;
    char *arg;
    int i;

    if (cmd->args->size == 0)
    {
        ft_printf("\n");
        return;
    }
    arg = cmd->args->get(cmd->args, 0);
    remove_line = should_remove_line(arg);
    i = -1;
    if (remove_line)
        i++;
    while (++i < cmd->args->size)
    {
        arg = cmd->args->get(cmd->args, i);
        if (strmatch("$?", arg))
            ft_printf("%d ", vars->status);
        else
            ft_printf("%s ", arg);
    }
    if (!remove_line)
        ft_printf("\n");
}

static bool    should_remove_line(char *flag)
{
    bool remove;
    int i;

    if (flag[0] != '-')
        return false;
    remove = true;
    i = 1;
    while (flag[i])
    {
        if (flag[i] != 'n')
        {
            remove = false;
            break;
        }
        i++;
    }
    return (remove);
}
