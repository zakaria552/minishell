/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:28:40 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:28:41 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_cmd *cmd)
{
	t_local_vars	*vars;
	int				i;

	i = -1;
	vars = get_local_vars();
	while (++i < cmd->args->size)
		vars->unset(cmd->args->get(cmd->args, i));
	vars->status = 0;
}
