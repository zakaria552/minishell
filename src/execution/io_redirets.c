#include "minishell.h"

static void   redirect_stdin(char *file);
static void   redirect_stdout(t_token *redirect);

void    redirect_stdin_pipe(t_vector *redirects, t_vector *pipes)
{
    int i;
    t_token *redir;
    t_token_type type;
    
    i = -1;
    ft_printf("Num of redirects: %d\n", redirects->size);
    while (++i < redirects->size)
    {
        ft_printf("%d\n", i);
        redir = (t_token *)redirects->get(redirects, i);
        type = redir->type;
		print_token(redir);
        if (type == INPUT_REDIR)
            redirect_stdin(redir->content);
    }
    ft_printf("Done redirecting\n");
}

static void   redirect_stdin(char *file)
{
    const int fd = open(file, O_RDONLY);
    int newfd;

    if (fd < 0)
    {
        runtime_err(file);
        exit(1);
    }
    newfd = dup2(fd, STDIN_FILENO);
    if (newfd < 0)
    {
        runtime_err(NULL);
        exit(1);
    }
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
    dup2(STDOUT_FILENO, fd);
}
