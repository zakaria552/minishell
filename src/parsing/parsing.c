#include "minishell.h"

t_vector	*tokenize_and_parse(char *s, t_arena *arena, char delimiter)
{
	t_vector	*tokens;
	t_vector	*commands;

	tokens = tokenize_input(s, arena, delimiter);
	if (!tokens)
		return (NULL);
	commands = parse_tokens_to_commands(arena, tokens);
	return (commands);
}

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

static t_cmd	*parse_single_command(t_arena *arena, t_vector *vec, int *i)
{
	t_cmd		*command;
	t_token		*tok;

	command = init_command(arena);
	*i -= 1;
	while (++(*i) < vec->size && !(command->unmatched_quote))
	{
		tok = vec->get(vec, *i);
		if (tok->type == EMPTY)
			continue ;
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
