/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:27:39 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/18 15:41:19 by nraatika         ###   ########.fr       */
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


static t_cmd *parse_single_command(t_arena *arena, t_vector *vec, int *i)
{
	t_cmd		*command;
	t_token		*tok;

	command = init_command(arena);
	*i -= 1;
	while (++(*i) < vec->size && !(command->unmatched_quote))
	{
		tok = vec->get(vec, *i);
		if (tok->type == EMPTY)
			continue;
		if (tok->type == PIPE)
			return (command);
		if (is_string_type(tok->type) || is_redirect_type(tok->type))
			update_command(arena, command, vec, i);
	}
	return (command);
}

//loops through the vector of tokens. 
//update command moves the index forward to the first non-string token 
//after any redirect token and any leading empty tokens
t_vector	*parse_tokens_to_commands(t_arena *arena, t_vector *vec)
{
	t_cmd		*command;
	t_vector	*table;
	int			i;

	if (vec->size == 0)
		return (NULL);
	table = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	command = init_command(arena);
	i = -1;
	while (++i < vec->size)
	{
		command = parse_single_command(arena, vec, &i);
		if (check_command(arena, command))
			append(table, command);
		else
			return (NULL);
	}
	if (((t_token *)vec->get(vec, vec->size - 1))->type == PIPE)
	{
		check_command(arena, init_command(arena));
		return (NULL);
	}
	return (table);
}
