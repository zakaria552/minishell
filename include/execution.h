#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// execution
void	execute_commands(t_vector *cmds, t_arena *arena);
void	redirect_io(t_cmd *cmd, bool redir_pipeline);
void	close_pipe(int pipe[2]);
char	*get_binary_path(char *command, char **envp, t_arena *arena);
void	execute_builtin(t_vector *cmds, int index, bool should_exit);
void	update_cmd_pipes(t_cmd *cmd, int *curr_pipe, int *next_pipe);

char	**envp_vars(void);

// here_doc handler
void	handle_here_doc(t_vector *cmds);
void	close_open_here_docs(t_vector *cmds, int index);

#endif
