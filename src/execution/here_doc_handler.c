#include "minishell.h"

static void set_cmd_here_doc(t_cmd *cmd, char *limiter);

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
        cmd->is_first_cmd = i == 0;
        cmd->is_last_cmd = i == cmds->size - 1;
        while (++j < cmd->redirects->size)
        {
            token = (t_token *)cmd->redirects->get(cmd->redirects, j);
            if (token->type != HERE_DOC)
                continue;
            //ft_printf("cmd-here_doc: %d\n",j);
            set_cmd_here_doc(cmd, token->content);
        }
    }
   set_readline_handler();
}

static void set_cmd_here_doc(t_cmd *cmd, char *limiter)
{
    const int len_limiter = ft_strlen(limiter);
    int hdoc_pipe[2];
    char *line;

    if (pipe(hdoc_pipe) < 0)
        runtime_err(errno, NULL);
	set_readline_handler();
    while (true)
    {
        line = read_prompt("> ", false);
        if (!line)
            runtime_err(errno, NULL);
        if (ft_strncmp(line, limiter, len_limiter) == 0 && !line[len_limiter
				+ 1])
			break ;
        if (write(hdoc_pipe[1], line, ft_strlen(line)) < 0)
            runtime_err(errno, NULL); 
    }
    if (cmd->fd_here_doc > 0)
        close(cmd->fd_here_doc);
    cmd->fd_here_doc = hdoc_pipe[0];
    close(hdoc_pipe[1]);
}

void    close_open_here_docs(t_vector *cmds, int index)
{
    t_cmd *cmd;
    int i;

    i = -1;
    while (++i < cmds->size)
    {
        cmd = (t_cmd *)(cmds->get(cmds, i));
        if (cmd->fd_here_doc > 0 && i != index)
            close(cmd->fd_here_doc);
    }
}
