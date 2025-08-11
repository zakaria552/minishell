/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:27:39 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/11 16:36:06 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_string_type(t_token_type type)
{
	if (type == QUOTE_SINGLE || type == QUOTE_DOUBLE)
		return (true);
	if (type == STRING || type == EXPANSION)
		return (true);
	return (false);
}

bool	is_redirect_type(t_token_type type)
{
	if (type == INPUT_REDIR || type == HERE_DOC)
		return (true);
	if (type == OUTPUT_REDIR || type == OUTPUT_APPEND)
		return (true);
	return (false);
}

/*
void	remove_empty_tokens(t_vector *vec)
{
	int		i;
	t_token	*temp;

	i = 0;
	while (i < vec->size)
	{
		temp = vec->get(vec, i);
		if (temp->type == EMPTY)
		{
			remove_element(vec, i);
			continue ;
		}
		++i;
	}
}
*/

//loops through the vector of tokens. 
//update command moves the index forward to the first non-string token 
//after any redirect token and any leading empty tokens
t_vector	*parse_vector_to_commands(t_arena *arena, t_vector *vec)
{
	t_cmd		*command;
	t_token		*tok;
	t_vector	*table;
	int			i;

	table = init_vector(1, NULL, arena);
	command = init_command(arena);
	i = -1;
	while (++i < vec->size)
	{
		tok = vec->get(vec, i);
		if (tok->type == EMPTY)
			continue;
		if (tok->type == PIPE)
		{
			append(table, command);
			command = init_command(arena);
		}
		if (is_string_type(tok->type) || is_redirect_type(tok->type))
			update_command(arena, command, vec, &i);
	}
	append(table, command);
	return (table);
}
