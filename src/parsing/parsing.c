/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:27:39 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/07 13:23:21 by nraatika         ###   ########.fr       */
/*   Updated: 2025/08/04 14:25:27 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "arena.h"

/*
	calculate how much of the input string belongs to the same token 
	(depends on type)
*/
static ssize_t	token_length(char *s, t_token_type type)
{
	(void)s;
	(void)type;
	return (0);
}

/*
	Return the type of token, which is determined by the first 1 o 2 characters
*/
static t_token_type get_type(char *s)
{
	t_token_type	type;

	type = EMPTY;
	if (*s == '>')
	{
		if (*(s+1) == '>')
			type = OUTPUT_APPEND;
		else
			type = OUTPUT_REDIR;
	}
	if (*s == '<')
	{
		if (*(s+1) == '<')
			type = HERE_DOC;
		else
			type = INPUT_REDIR;
	}
	if (*s == '|')
		type = PIPE;
	if (*s == '\'')
		type = QUOTE_SINGLE;
	if (*s == '"')
		type = QUOTE_DOUBLE;
	if (*s == '$')
		type = EXPANSION;
	if (ft_isalpha(*s))
		type = STRING;
	return (type);
}

/*
	check the type of token, then make a token that contains the type, length
	and content of the token
*/
static t_token	*get_next_token(char *s, t_arena *arena)
{
	t_token	tok;
	char	*content;

	tok.type = get_type(s);
	tok.read_chars = token_length(s, tok.type);
	if (tok.read_chars != -1)
	{
		content = ft_calloc(1, tok.read_chars + 1);
		ft_memcpy(content, s, tok.read_chars);
		tok.content = arena_alloc(arena, tok.read_chars + 1, content);
		free(content);
	}
	else
		tok.content = NULL;
	return (arena_alloc(arena, sizeof(t_token), &tok));
}

//parse the input string, store the parsed input as a vector of tokens (TODO)
void	parse_input(char *s, t_arena *arena)
{
	size_t		len;
	t_token		*tok;

	len = ft_strlen(s);
	while (s && len > 0)
	{
		tok = get_next_token(s, arena);
		s += tok->read_chars;
		len -= tok->read_chars;
	}
}
