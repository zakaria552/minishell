#include "minishell.h"

char	*strip_quotes(t_arena *arena, char *str, bool should_strip)
{
	char	*stripped;

	if (should_strip)
	{
		stripped =  arena_alloc(arena, ft_strlen(str) - 1, str + 1);
		stripped[ft_strlen(str) - 2] = '\0';
		return (stripped);
	}
	else 
		return (str);
}

//strips the first and last character from QUOTE tokens, and expands possible
//variables in double quoted tokens, expands EXPANSION tokens
static char	*strip_expand(t_token *tok, t_arena *arena, bool expand)
{
	char	*str;
	char	*start;

	if (tok->type == QUOTE_DOUBLE || tok->type == QUOTE_SINGLE )
	{
		str = strip_quotes(arena, tok->content, expand);
		if (tok->type == QUOTE_DOUBLE)
		{
			start = ft_strchr(str, '$');
			if (start != NULL && expand)
				str = handle_expansion(arena, str, start);
		}
		return (str);
	}
	if (tok->type == EXPANSION && expand)
		return (handle_expansion(arena, tok->content, tok->content));
	return (tok->content);
}

static void	skip_empties(t_vector *vec, int *i)
{
	while (*i < vec->size && ((t_token *)vec->get(vec, *i))->type == EMPTY)
		*i += 1;
}

//concatenates any unbroken sequence of string-type tokens to the return,
//starting at the index pointed to by i, updates the index as it goes along
//skips any leading empty tokens
//returns NULL if it encounters string-type tokens with NULL content,
//which happens only with unmatched quotes.
char	*concat_string_types(t_arena *arena, t_vector *vec, int *i, bool x)
{
	char		*string;
	char		*temp;
	t_token		*tok;
	
	string = arena_strdup(arena, "");
	skip_empties(vec, i);
	while (*i < vec->size)
	{
	 	tok = vec->get(vec, *i);
		if (is_string_type(tok->type))
		{
			temp = arena_strjoin(arena, string, strip_expand(tok, arena, x));
			string = temp;
		}
		else
		{
			*i -= 1;
			break;
		}	
		*i += 1;
	}
	return (string);
}
