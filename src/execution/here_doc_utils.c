/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:23 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/09 16:53:31 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*arena_itoa(int num, t_arena *arena);
static int	str_num_length(int num);
static char *file_name_by_index(int index);

void	close_open_here_docs(t_vector *cmds, int index)
{
	t_cmd	*cmd;
	int		i;
	char *file;

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
	i = 0;
	while (index == -1  && ++i)
	{
		file = file_name_by_index(i);
		if (access(file, F_OK) < 0)
			break;
		unlink(file);
	}
}

char *here_doc_file(void)
{
	char *file;
	int i;	
	
	i = 0;
	while (++i)
	{
		file = file_name_by_index(i);
		if (access(file, F_OK) < 0)
			break;
	}
	return (file);
}

static char	*arena_itoa(int num, t_arena *arena)
{
	char	*str_num;
	int		str_len;
	int		sign;
	long	n;

	str_len = str_num_length(num);
	str_num = arena->alloc(arena, (str_len + 1) * sizeof(char), NULL);
	sign = 1;
	n = num;
	str_num[str_len] = '\0';
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	while (--str_len >= 0)
	{
		str_num[str_len] = n % 10 + '0';
		n = n / 10;
		if (str_len == 0 && sign < 0)
			str_num[0] = '-';
	}
	return (str_num);
}

static int	str_num_length(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static char *file_name_by_index(int index)
{
	t_arena *arena = get_allocators()->prompt;
	char *file = "/tmp/.mini-here-doc-";
	
	return arena_strjoin(arena, file, arena_itoa(index, arena));
}