#include "minishell.h"

static void   redirect_stdin(char *file);
static void   redirect_stdout(t_token *redirect);
static void     redirect_here_doc(t_cmd *cmd);
static void     pipe_redirect(t_cmd *cmd);

void    redirect_io(t_cmd *cmd)
{
    const t_vector *redirects = cmd->redirects;
    t_token *redir;
    t_token_type type;
    int i;
    
    redirects = cmd->redirects;
    i = -1;
    redirect_here_doc(cmd);
    pipe_redirect(cmd);
    while (++i < redirects->size)
    {
        ft_putnbr_fd(i, 2);
        redir = (t_token *)redirects->get(redirects, i);
        type = redir->type;
        if (type == INPUT_REDIR)
            redirect_stdin(redir->content);
        else if (type == OUTPUT_REDIR)
            redirect_stdout(redir);
    }
}

static void   redirect_stdin(char *file)
{
    const int fd = open(file, O_RDONLY);

    if (fd < 0)
        runtime_err(errno, file);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        runtime_err(errno, NULL);
    }
    close(fd);
}

static void   redirect_stdout(t_token *redirect)
{
    int fd;
    int flags;
    int mode;
    
    flags = O_RDWR | O_CREAT;
    mode = 0;
    mode |= S_IRUSR | S_IWUSR;
    mode |= S_IRGRP;
    mode |= S_IROTH;
    if (redirect->type == OUTPUT_APPEND)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open(redirect->content, flags, mode);
    if (fd < 0)
        runtime_err(errno, NULL);
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        close(fd);
        runtime_err(errno, NULL);
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
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close_pipe(cmd->curr_pipe);
        close_pipe(cmd->next_pipe);
        close(fd);
        runtime_err(errno, NULL);
    }
    close(fd);
}