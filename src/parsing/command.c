/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:12:40 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/18 15:31:34 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_command(t_arena *arena)
{
	t_cmd	*command;

	command = arena_alloc(arena, sizeof(t_cmd), NULL);
	command->args = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	command->redirects = init_vector(INIT_VECTOR_SIZE, NULL, arena);
	return (command);
}

static char	*contains_expansions(char *s)
{
	return (ft_strchr(s, '$'));
}

//expands the variable name of length len starting at s, 
//returns empty string if no variable of that name exists.
char	*expand_variable(t_arena * arena, char *s, int len)
{
	char	*var_name;
	char	*var;

	var_name = arena_alloc(arena, len, s + 1);
	var_name[len - 1] = '\0';
	var = getenv(var_name);
	if (!var)
		return (arena_strdup(arena, ""));
	return (var);
}

//handles the expansion of a variable, for both EXPANSION type tokens
//that have one $VARIABLE, and QUOTE_DOUBLE tokens that may have multiple
static char	*handle_expansion(t_arena *arena, char *s, char *start)
{
	char	*string;
	char	*temp;
	int		len;
	
	if (!*s || (*s && !*(s + 1)))
		return (arena_strdup(arena, s));
	if (start != NULL)
	{
		string = arena_alloc(arena, s - start + 1, NULL);
		ft_memcpy(string, s, s - start);
		len = expansion_length(start);
		temp = arena_strjoin(arena, string, expand_variable(arena, start, len));
		string = temp;
		temp = arena_strjoin(arena, string, handle_expansion(arena, \
			start + len, contains_expansions(start + len)));
		string = temp;
	}
	else 
		return (arena_strdup(arena, s));
	return (string);
}

//strips the first and last character from QUOTE tokens, and expands possible
//variables in double quoted tokens, expands EXPANSION tokens
static char	*strip_expand(t_token *tok, t_arena *arena)
{
	char	*str;
	char	*start;

	if (tok->type == QUOTE_DOUBLE)
	{
		if (!(tok->content))
			return (NULL);
		str = arena_alloc(arena, ft_strlen(tok->content) - 1, tok->content + 1);
		str[ft_strlen(tok->content) - 2] = '\0';
		start = contains_expansions(str);
		if (start != NULL)
			str = handle_expansion(arena, str, start);
		return (str);
	}
	if (tok->type == QUOTE_SINGLE)
	{
		if (!(tok->content))
			return (NULL);
		str = arena_alloc(arena, ft_strlen(tok->content) - 1, tok->content + 1);
		str[ft_strlen(tok->content) - 2] = '\0';
		return (str);
	}
	if (tok->type == EXPANSION)
		return (handle_expansion(arena, tok->content, tok->content));
	return (tok->content);
}

//updates a command with either a command, an argument, or a redirect
//and moves the index forward by however many tokens were used to do so
void	update_command(t_arena *arena, t_cmd *command, t_vector *vec, int *i)
{
	t_token	*tok;
	char	*temp;

	tok = vec->get(vec, *i);
	if(is_string_type(tok->type))
	{
		temp = concat_string_type_tokens(arena, vec, i);
		if (temp)
		{
			if (command->cmd == NULL)
				command->cmd = temp;
			else
				append(command->args, temp);
		}
		else
			command->unmatched_quote = tok->type;
	}
	if(is_redirect_type(tok->type))
	{
		*i += 1;
		temp = concat_string_type_tokens(arena, vec, i);
		if (temp)
		{
			tok->content = temp;
			append(command->redirects, tok);
		}
		else
			command->unmatched_quote = tok->type;
		tok->content = concat_string_type_tokens(arena, vec, i);
		append(command->redirects, tok);
	}
}

//concatenates any unbroken sequence of string-type tokens to the return,
//starting at the index pointed to by i, updates the index as it goes along
//skips any leading empty tokens
//returns NULL if it encounters string-type tokens with NULL content,
//which happens only with unmatched quotes.
char	*concat_string_type_tokens(t_arena *arena, t_vector *vec, int *i)
{
	char		*string;
	char		*temp;
	t_token		*tok;
	
	string = arena_strdup(arena, "");
	while (*i < vec->size && ((t_token *)vec->get(vec, *i))->type == EMPTY)
		*i += 1;	
	while (*i < vec->size)
	{
	 	tok = vec->get(vec, *i);
		if (is_string_type(tok->type))
		{
			if (!tok->content)
				return (NULL);
			temp = arena_strjoin(arena, string, strip_expand(tok, arena));
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

void	print_vector_commands(t_vector *vec)
{
	int i;

	i = -1;
	while (++i < vec->size)
		print_command((t_cmd *)vec->get(vec, i));
}

void	print_command(t_cmd *command)
{
	int	i;

	ft_printf("\n***\ncommand: %s\n", command->cmd);
	i = -1;
	while (++i < command->args->size)
		ft_printf("arg%d: %s\n", i, (char *)command->args->get(command->args, i));
	i = -1;
	if (command->redirects->size > 0)
		ft_printf("redirects:\n");
	while (++i < command->redirects->size)
		print_token((t_token *)command->redirects->get(command->redirects, i));
	ft_printf("***\n");
}
