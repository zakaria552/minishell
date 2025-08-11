#include "minishell.h"

static void   redirect_stdin(char *file);
static void   redirect_stdout(t_token *redirect);
static void     redirect_here_doc(t_cmd *cmd);

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
    redirect_here_doc(cmd);
    ft_putstr_fd("Done redirecting\n", 2);
}

static void   redirect_stdin(char *file)
{
    const int fd = open(file, O_RDONLY);

    if (fd < 0)
        runtime_err(file);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        runtime_err(NULL);
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
    if (fd < 0)
        runtime_err(NULL);
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        close(fd);
        runtime_err(NULL);
    }
    close(fd);
}

static void     redirect_here_doc(t_cmd *cmd)
{
    t_token *last_redirect;
    const int fd = cmd->fd_here_doc;
    
    if (cmd->redirects->size == 0 || fd < 0) 
        return ;
    
    last_redirect = (t_token *)cmd->redirects->get(cmd->redirects, cmd->redirects->size - 1);
    if (last_redirect->type != HERE_DOC)
    {
        close(fd);
        return ;
    }
    ft_putstr_fd("Here doc: ", 2);
    ft_putnbr_fd(fd, 2);
    ft_putstr_fd("\n", 2);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        runtime_err(NULL);
    }
    ft_putstr_fd("###########\n", 2);
    close(fd);
}