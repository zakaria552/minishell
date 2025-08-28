#include "minishell.h"

//handle expanding a single '$' EXPANSION token:
//turns any EXPANSION type with content '$' NOT followed by EMPTY or PIPE
//into STRING with content ''
void	expand_single_dollar(t_vector *vec, t_arena *arena)
{
	t_token	*tok;
	t_token *next;
	int 	i;

	i = -1;
	while (++i < vec->size)
	{
		tok = vec->get(vec, i);
		if (tok->type == EXPANSION && strmatch(tok->content, "$"))
		{
			next = vec->get(vec, i + 1);
			if (!next || (next->type == EMPTY || next->type == PIPE))
				continue ;
			tok->type = STRING;
			tok->content = arena_strdup(arena, "");
		}
	}
}

//expands the variable name of length len starting at s, 
//returns empty string if no variable of that name exists.
char	*expand_variable(t_arena * arena, char *s)
{
	t_local_vars *vars;
	t_env_var *var;
	char	*var_name;
	int	len;
	
	len = expansion_length(s);
	vars = get_local_vars();
	if (len == 2 && *(s + 1) == '?')
		return (arena_int_to_string(arena, vars->status));
	if (len == 1)
		return (arena_strdup(arena, "$"));
	var_name = arena_alloc(arena, len, s + 1);
	var_name[len - 1] = '\0';
	var = get_var(var_name);
	if (!var)
		return (arena_strdup(arena, ""));
	return (var->value);
}

//handles the expansion of a variable, for both EXPANSION type tokens
//that have one $VARIABLE, and QUOTE_DOUBLE tokens that may have multiple
//boolean 'single' tells whether to expand a single $ to '$' rather than ''
//happens when EXPANSION type is followed by EMPTY, or within double quotes
char	*handle_expansion(t_arena *arena, char *s, char *start)
{
	char	*string;
	char	*temp;
	int		len;
	
	if (!*s || (*s && !*(s + 1)))
		return (arena_strdup(arena, s));
	if (start != NULL)
	{
		string = arena_alloc(arena, (start - s) + 1, s);
		string[(start - s)] = '\0';
		len = expansion_length(start);
		temp = arena_strjoin(arena, string, expand_variable(arena, start));
		string = temp;
		temp = arena_strjoin(arena, string, handle_expansion(arena, \
			start + len, ft_strchr(start + len, '$')));
		string = temp;
	}
	else 
		return (arena_strdup(arena, s));
	return (string);
}


