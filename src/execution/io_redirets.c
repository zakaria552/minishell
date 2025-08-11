#include "minishell.h"

static void   redirect_stdin(char *file);
static void   redirect_stdout(t_token *redirect);

void    redirect_io(t_cmd *cmd)
{
    const t_vector *redirects = cmd->redirects;
    t_token *redir;
    t_token_type type;
    int i;
    
    i = -1;
    ft_printf("io-redirects\n");
    ft_printf("Is last cmd: %d\n", cmd->is_last_cmd);
    ft_printf("Size: %d\n", redirects->size);
    if (dup2(cmd->curr_pipe[0], STDIN_FILENO) < 0 ||
        (!cmd->is_last_cmd && dup2(cmd->next_pipe[1], STDOUT_FILENO) < 0))
        runtime_err(NULL);
    close_pipe(cmd->curr_pipe);
    close_pipe(cmd->next_pipe);
    while (++i < redirects->size)
    {
        ft_putnbr_fd(i, 2);
        redir = (t_token *)redirects->get(redirects, i);
        type = redir->type;
		//print_token(redir);
        if (type == INPUT_REDIR)
            redirect_stdin(redir->content);
        else if (type == OUTPUT_REDIR)
            redirect_stdout(redir);
    }
    ft_putstr_fd("Done redirecting\n", 2);
}

static void   redirect_stdin(char *file)
{
    const int fd = open(file, O_RDONLY);

    if (fd < 0)
    {
        runtime_err(file);
        exit(1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        runtime_err(NULL);
        exit(1);
    }
    close(fd);
}

static void   redirect_stdout(t_token *redirect)
{
    int fd;
    int flags;
    
    flags = O_CREAT | O_WRONLY;
    if (redirect->type == OUTPUT_APPEND)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open(redirect->content, flags);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}
