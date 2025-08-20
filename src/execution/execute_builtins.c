#include "minishell.h"

static void    exc_builtin(t_cmd *cmd, t_local_vars *vars, bool *should_exit);

void    execute_builtin(t_vector *cmds, int index, bool should_exit, bool pipeline)
{
    const t_cmd *cmd = cmds->get(cmds, index);
    t_local_vars *vars;

    vars = get_local_vars();
    if (!is_builtin(cmd->cmd))
        return;
    vars->stdin_cpy = dup(STDIN_FILENO);
    vars->stdout_cpy = dup(STDOUT_FILENO);
    if (vars->stdin_cpy < 0)
        runtime_err(errno, NULL);
    if (vars->stdout_cpy < 0) 
    {
        close(vars->stdin_cpy);
        runtime_err(errno, NULL);
    }
    if (!pipeline)
        redirect_io((t_cmd *)cmd, false);
    exc_builtin((t_cmd *)cmd, vars, &should_exit);
    if(should_exit || pipeline)
    {
        close_open_here_docs(cmds, -1);
        clean_up(true, true);
        exit(vars->status);
    }
}

static void    exc_builtin(t_cmd *cmd, t_local_vars *vars, bool *should_exit)
{
    if (strmatch(cmd->cmd, "export"))
        export((t_cmd *)cmd);
    else if (strmatch(cmd->cmd, "unset"))
        unset((t_cmd *)cmd);
    else if (strmatch(cmd->cmd, "env"))
        env();
    else if (strmatch(cmd->cmd, "exit"))
        builtin_exit((t_cmd*) cmd, should_exit);
    else if (strmatch(cmd->cmd, "echo"))
        echo(cmd);
    if (dup2(vars->stdin_cpy, STDIN_FILENO) < 0 || dup2(vars->stdout_cpy, STDOUT_FILENO) < 0)
    {
        close(vars->stdin_cpy);
        close(vars->stdout_cpy);
        runtime_err(errno, NULL);
    }
    close(vars->stdin_cpy);
    close(vars->stdout_cpy);
}

char **envp_vars(void)
{
    const t_allocators *allocs = get_allocators();
    const t_local_vars *vars = get_local_vars();
    const size_t size = sizeof(char *) * (vars->envp->size + 1);
    t_env_var *var;
    char **envp;
    int i;

    i = -1;
    envp = allocs->prompt->alloc(allocs->prompt, size, NULL);
    while (++i < vars->envp->size)
    {
        var = vars->envp->get(vars->envp, i);
        envp[i] = var->joint;
    }
    envp[i] = NULL;
    return (envp);
}