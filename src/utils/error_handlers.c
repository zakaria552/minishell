#include "minishell.h"

void    clean_up(bool clean_global, bool clean_history)
{
    t_allocators *allocs = get_allocators();

    if (allocs->global && clean_global)
        allocs->global->destroy(allocs->global);
    if (allocs->prompt)
        allocs->prompt->destroy(allocs->prompt);
    if (clean_history)
        clear_history();
}

void    syntax_err(int err_code, char *msg)
{
    errno = err_code;
    ft_putstr_fd("Minishell: ", STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    clean_up(false, false);

}

void    runtime_err(int err_code, char *msg)
{
    errno = err_code;
    ft_putstr_fd("minishell: ", 2);
    if (msg)
    {
        ft_putstr_fd(msg, 2);
        ft_putstr_fd(":", 2);
    }
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    clean_up(true, true);
    exit(errno);
}

void    cmd_not_found_err(int err_code, char *cmd, bool path_exist)
{
    if (err_code != 127)
        runtime_err(errno, cmd);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(":", 2);
    if (path_exist)
        ft_putstr_fd("command not found\n", 2);
    else
        ft_putstr_fd("No such file or directory\n", 2);
    clean_up(true, true);
}
