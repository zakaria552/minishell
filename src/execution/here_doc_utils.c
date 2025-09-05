/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:23 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:30:24 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_open_here_docs(t_vector *cmds, int index)
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	while (++i < cmds->size)
	{
		cmd = (t_cmd *)(cmds->get(cmds, i));
		if (cmd->fd_here_doc > 0 && i != index)
		{
			close(cmd->fd_here_doc);
			cmd->fd_here_doc = -1;
		}
	}
}
