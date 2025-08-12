/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:29:01 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/15 13:56:10 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_redirect(t_arena *arena, t_token *token)
{
	char *error;

	if (ft_strlen(token->content) >= 1)
		return (true);
	else
	{
		error = arena_strjoin(arena, "syntax error, empty redirect: ",\
		 (char *)get_token_type(token->type));
		ft_error(error);
		return (false);
	}
}

bool check_command(t_arena *arena, t_cmd *command)
{
	char	*error;
	int		i;

	if (!command->cmd)
	{
		error = arena_strdup(arena, "syntax error, pipe with no command");
		ft_error(error);
		return (false);
	}
	i = 0;
	while (i++ < command->redirects->size)
	{
		if (!check_redirect(arena, get_vector_elem(command->redirects, i)))
			return (false);
	}
	return (true);
}
