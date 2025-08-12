/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:29:01 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/12 16:49:32 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_redirect(t_token *token)
{
	if (ft_strlen(token->content) >= 1)
		return (true);
	else
	{
		ft_printf("syntax error:empty redirect\n");
		return (false);
	}
}

bool check_command(t_cmd *command)
{
	if (!command->cmd)
	{
		ft_printf("syntax_error: no command in pipe\n");
		return (false);
	}
	else
		return (true);
}
