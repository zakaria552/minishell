#ifndef EXECUTION_H
#define EXECUTION_H

#include "minishell.h"

// execution
void    execution(t_vector *cmds, t_arena *arena, char **envp);
void    redirect_io(t_cmd *cmd);
void    close_pipe(int pipe[2]);
char	*format_path(char *command, char **envp, t_arena *arena);

// here_doc handler
void    handle_here_doc(t_vector *cmds);

// error handler
void    runtime_err(char *msg);
#endif