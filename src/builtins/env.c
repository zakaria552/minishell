/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:28:20 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:28:21 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(void)
{
	t_local_vars	*vars;
	t_env_var		*var;
	int				i;

	i = -1;
	vars = get_local_vars();
	while (++i < vars->envp->size)
	{
		var = vars->envp->get(vars->envp, i);
		if (var->value)
			ft_printf("%s\n", var->joint);
	}
	vars->status = 0;
}
