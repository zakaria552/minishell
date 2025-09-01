#include "minishell.h"

const char	*get_token_type(t_token_type type)
{
	const char	*names[] = {"EMPTY", "PIPE", "INPUT_REDIR", "OUTPUT_REDIR", \
"OUTPUT_APPEND", "HERE_DOC", "QUOTE_SINGLE", "QUOTE_DOUBLE", "EXPANSION", \
"STRING"};

	return (names[type]);
}

/*
	calculate how much of the input string belongs to the same token 
	(depends on type)
*/
static ssize_t	token_length(char *s, t_token_type type)
{
	t_token_length_func	token_length_func;
	ssize_t				length;

	if (type == QUOTE_SINGLE)
		token_length_func = single_quote_length;
	else if (type == QUOTE_DOUBLE)
		token_length_func = double_quote_length;
	else if (type == STRING)
		token_length_func = string_length;
	else if (type == EXPANSION)
		token_length_func = expansion_length;
	else if (type == EMPTY)
		token_length_func = empty_length;
	else
		token_length_func = dummy_length;
	length = token_length_func(s);
	return (length);
}

/*
	Return the type of token, which is determined by the first 1 or 2 characters
*/
static t_token_type	get_type(char *s)
{
	if (*s == '>')
	{
		if (*(s + 1) == '>')
			return (OUTPUT_APPEND);
		else
			return (OUTPUT_REDIR);
	}
	if (*s == '<')
	{
		if (*(s + 1) == '<')
			return (HERE_DOC);
		else
			return (INPUT_REDIR);
	}
	if (*s == '|')
		return (PIPE);
	if (*s == '\'')
		return (QUOTE_SINGLE);
	if (*s == '"')
		return (QUOTE_DOUBLE);
	if (*s == '$')
		return (EXPANSION);
	if (!is_string_delimiter(*s))
		return (STRING);
	return (EMPTY);
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

//tokenize the input string, return a vector of commands by first making a 
//a vector of tokens, and then calling a command to parse them to commands. 
t_vector	*tokenize_input(char *s, t_arena *arena, char delimiter)
{
	t_token		*tok;
	t_vector	*tokens;

	tokens = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	while (s && *s && *s != delimiter)
	{
		tok = get_next_token(s, arena);
		tokens->push(tokens, tok);
		if (tok->read_chars > 0)
			s += tok->read_chars;
		else
		{
			syntax_err(2, "unmatched quote");
			return (NULL);
		}
	}
	expand_single_dollar(tokens, arena);
	return (tokens);
}
