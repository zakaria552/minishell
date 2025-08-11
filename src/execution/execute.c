#include "minishell.h"

void execute_cmd(t_cmd *cmd, char **envp, t_arena *arena);

static void wait_child_processes(t_vector *cmds, int *status);

void    execution(t_vector *cmds, t_arena *arena, char **envp)
{
    t_cmd *cmd;
    int curr_pipe[2];
    int next_pipe[2];
    int status;
    int i;

    i = -1;
    if (pipe(curr_pipe) < 0)
        clean_exit(arena, errno, NULL);
    while (++i < cmds->size)
    {
        cmd = ((t_cmd *) cmds->get(cmds, i));
        ft_printf("Command: %s\n", cmd->cmd);
        ft_printf("c-pipe: [%d][%d]\n", curr_pipe[0], curr_pipe[1]);
        if (pipe(next_pipe) < 0)
            clean_exit(arena, errno, NULL);
        ft_printf("n-pipe: [%d][%d]\n", next_pipe[0], next_pipe[1]);
        ft_memcpy(cmd->curr_pipe, curr_pipe, sizeof(curr_pipe));
        ft_memcpy(cmd->next_pipe, next_pipe, sizeof(next_pipe));
        cmd->pid = fork();
        cmd->is_last_cmd = i == cmds->size - 1;
        if (cmd->pid < 0)
            clean_exit(arena, errno, NULL);
        if (cmd->pid == 0)
            execute_cmd((t_cmd *)(cmds->get(cmds, i)), envp, arena);
        close_pipe(curr_pipe);
        ft_memcpy(curr_pipe, next_pipe, sizeof(curr_pipe));
    }
    wait_child_processes(cmds, &status);
    ft_printf("Last status: %d\n", WEXITSTATUS(status));
}

void execute_cmd(t_cmd *cmd, char **envp, t_arena *arena)
{
    char *binary_path = format_path(cmd->cmd, envp, arena);
    ft_printf("Path: %s\n", binary_path);
    redirect_io(cmd);
    ft_putstr_fd("--->\n", 2);
    execve(binary_path, cmd->args, envp);
    ft_putstr_fd("command failed", 2);
    
    exit(errno);
}

void    close_pipe(int pipe[2])
{
    close(pipe[0]);
    close(pipe[1]);
}

static void wait_child_processes(t_vector *cmds, int *status)
{
    int i;
    t_cmd *cmd;

    i = -1;
    while (++i < cmds->size)
    {
        cmd = ((t_cmd *) cmds->get(cmds, i));
        waitpid(cmd->pid, status, 0);
    }
}