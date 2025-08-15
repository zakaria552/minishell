/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:27:39 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/15 14:07:20 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//debug function
void	print_token(t_token *tok)
{
	ft_printf("Type:%s Length:%d Content:%s\n", get_token_type(tok->type),\
		tok->read_chars, tok->content);
}

const char	*get_token_type(t_token_type type)
{
	const char *names[] = {"EMPTY", "PIPE", "INPUT_REDIR", "OUTPUT_REDIR",\
		"OUTPUT_APPEND", "HERE_DOC", "QUOTE_SINGLE", "QUOTE_DOUBLE", \
		"EXPANSION", "STRING"};

	return (names[type]);
}

//Different functions for different token types
static t_token_length_func	get_length_function(t_token_type type)
{
	if (type == QUOTE_SINGLE)
		return single_quote_length;
	if (type == QUOTE_DOUBLE)
		return double_quote_length;
	if (type == STRING)
		return string_length;
	if (type == EXPANSION)
		return expansion_length;
	if (type == EMPTY)
		return empty_length;
	else
		return dummy_length;
}

/*
	calculate how much of the input string belongs to the same token 
	(depends on type)
*/
static ssize_t	token_length(char *s, t_token_type type)
{
	t_token_length_func	token_length_func;
	ssize_t				length;

	token_length_func = get_length_function(type);
	length = token_length_func(s);
	return (length);
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
	if (!is_string_delimiter(*s))
		type = STRING;
	return (type);
}

/*
	check the type of token, then make a token that contains the type, length
	and content of the token.  
*/
static t_token	*get_next_token(char *s, t_arena *arena)
{
	t_token	*tok;
	char	*content;

	tok = arena_alloc(arena, sizeof(t_token), NULL);
	tok->type = get_type(s);
	tok->read_chars = token_length(s, tok->type);
	if (tok->read_chars != -1)
	{
		content = arena_alloc(arena, tok->read_chars + 1, NULL);
		ft_memcpy(content, s, tok->read_chars);
		tok->content = content;
	}
	else
		tok->content = NULL;
	return (tok);
}

//tokenize the input string, return a vector of tokens
//delimiter is there so the function can be reused to tokenize quoted strings
//for parsing. 
t_vector	*tokenize_input(char *s, t_arena *arena, char delimiter)
{
	t_token		*tok;
	t_vector	*vec;

	vec = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	while (s && *s && *s != delimiter)
	{
		tok = get_next_token(s, arena);
		vec->push(vec, tok);
		if (tok->read_chars > 0)
			s += tok->read_chars;
		else 
			syntax_err(3, "token length < 1");
	}
	return (vec);
}
