#include "minishell.h"

static void execute_cmd(t_cmd *cmd, char **envp, t_arena *arena);
static char **execve_args(t_arena *arena, t_cmd *cmd, char *binary);
static void wait_child_processes(t_vector *cmds, int *status);
void    print_args(char **args);

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
        if (pipe(next_pipe) < 0)
            clean_exit(arena, errno, NULL);
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

static void execute_cmd(t_cmd *cmd, char **envp, t_arena *arena)
{
    char *binary_path;
    char **args;

    ft_printf("curr-pipe: [%d][%d], next-pipe: [%d][%d]\n", cmd->curr_pipe[0], cmd->curr_pipe[1],
        cmd->next_pipe[0], cmd->next_pipe[1]);
    binary_path = format_path(cmd->cmd, envp, arena); // refactor the format path
    if (!binary_path)
        clean_exit(arena, errno, cmd->cmd);
    args = execve_args(arena, cmd, binary_path);
    print_args(args);
    redirect_io(cmd);
    execve(binary_path, args, envp);
    ft_putstr_fd("execve errored\n", 2);
    exit(errno);
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

static char **execve_args(t_arena *arena, t_cmd *cmd, char *binary)
{
    t_vector *cmd_args;
    char **args;
    int i;

    cmd_args = cmd->args;
    args = arena->alloc(arena, sizeof(char *) * (cmd_args->size + 2), NULL);
    args[0] = binary;
    i = -1;
    while (++i < cmd_args->size)
        args[i + 1] = cmd_args->get(cmd_args, i);
    args[i + 1] = NULL;
    return args;
}

void    close_pipe(int pipe[2])
{
    close(pipe[0]);
    close(pipe[1]);
}
// to be removed
void    print_args(char **args)
{
    int i = 0;
    ft_putstr_fd("Arguments:-->", 2);
    while (args[i])
        ft_printf("[%s]-", args[i++]);
    ft_putstr_fd("\n", 2);
}