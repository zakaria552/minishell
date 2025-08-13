#include "minishell.h"

void set_cmd_here_doc(t_cmd *cmd, char *limiter);
bool    seterrno(int err_code);

void    handle_here_doc(t_vector *cmds)
{
    t_cmd *cmd;
    t_token *token;
    int i;
    int j;

    i = -1;
    while (++i < cmds->size)
    {
        cmd = (t_cmd *)(cmds->get(cmds, i));
        j = -1;
        cmd->fd_here_doc = -1;
        while (++j < cmd->redirects->size)
        {
            token = (t_token *)cmd->redirects->get(cmd->redirects, j);
            if (token->type != HERE_DOC)
                continue;
            ft_printf("cmd-here_doc: %d\n",j);
            set_cmd_here_doc(cmd, token->content);
        }
    }
}

void set_cmd_here_doc(t_cmd *cmd, char *limiter)
{
    const int len_limiter = ft_strlen(limiter);
    int hdoc_pipe[2];
    char *line;

    if (pipe(hdoc_pipe) < 0)
        runtime_err(strerror(errno));
    while (true)
    {
        ft_printf("> ");
        // use the readline, allocate on the arena
        line = get_next_line(STDIN_FILENO);
        if (!line)
            clean_exit(NULL, ENOMEDIUM, strerror(ENOMEDIUM));
        if (write(hdoc_pipe[1], line, ft_strlen(line)) < 0)
            runtime_err(strerror(errno));
        if (ft_strncmp(line, limiter, len_limiter) == 0 && !line[len_limiter
				+ 1])
			break ;
        free(line);
    }
    if (cmd->fd_here_doc > 0)
        close(cmd->fd_here_doc);
    cmd->fd_here_doc = hdoc_pipe[0];
    close(hdoc_pipe[1]);
}

bool    seterrno(int err_code)
{
    errno = err_code;
    return (true);
}