#include "minishell.h"

void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	update_cmd_pipes(t_cmd *cmd, int *curr_pipe, int *next_pipe)
{
	ft_memcpy(cmd->curr_pipe, curr_pipe, sizeof(curr_pipe));
	ft_memcpy(cmd->next_pipe, next_pipe, sizeof(next_pipe));
}
