#ifndef EXECUTION_H
#define EXECUTION_H

#include "minishell.h"


void    redirect_io(t_cmd *cmd);
void    execution(t_vector *cmds, t_arena *arena, char **envp);
void    here_docs(t_vector *cmds);

// error handler
void    runtime_err(char *msg);
void    close_pipe(int pipe[2]);
char	*format_path(char *command, char **envp, t_arena *arena);
#endif