/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:12:40 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/11 17:36:16 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_command(t_arena *arena)
{
	t_cmd	*command;

	command = arena_alloc(arena, sizeof(t_cmd), NULL);
	command->args = init_vector(1, NULL, arena);
	command->redirects = init_vector(1, NULL, arena);
	return (command);
}

static int	expansion_end(char *s)
{
	int i;

	i = 1;
	while (*(s + i))
	{
		if (*(s + i) == '$' || ft_isspace(*(s+i)))
			return (i);
		++i;
	}
	return (i);
}

static char	*contains_expansions(char *s)
{
	return (ft_strchr(s, '$'));
}

static char	*handle_expansion(t_arena *arena, char *s, char *start)
{
	char	*string;
	char	*temp;
	int		len;
	
	if (start != NULL)
	{
		string = arena_alloc(arena, s - start + 1, s);
		ft_memcpy(string, s, s - start);
		len = expansion_end(start);
		temp = arena_strjoin(arena, string, arena_strdup(arena, "(TODO:EXPANSION)"));
		string = temp;
		temp = arena_strjoin(arena, string, handle_expansion(arena, \
			start + len, contains_expansions(start + len)));
		string = temp;
	}
	else 
		return (arena_strdup(arena, s));
	return (string);
}

static char	*strip_expand(t_token *tok, t_arena *arena)
{
	char	*string;
	char	*start;

	if (tok->type == QUOTE_DOUBLE)
	{
		string = arena_alloc(arena, ft_strlen(tok->content) - 1, tok->content + 1);
		string[ft_strlen(tok->content) - 2] = '\0';
		start = contains_expansions(string);
		if (start != NULL)
			string = handle_expansion(arena, string, start);
		return (string);
	}
	if (tok->type == QUOTE_SINGLE)
	{
		string = arena_alloc(arena, ft_strlen(tok->content) - 1, tok->content + 1);
		string[ft_strlen(tok->content) - 2] = '\0';
		return (string);
	}
	if (tok->type == EXPANSION)
		return (handle_expansion(arena, tok->content, tok->content));
	return (tok->content);
}

void	update_command(t_arena *arena, t_cmd *command, t_vector *vec, int *i)
{
	t_token	*tok;

	tok = vec->get(vec, *i);
	if(is_string_type(tok->type))
	{
		if (command->cmd == NULL)
			command->cmd = concat_string_type_tokens(arena, vec, i);
		else
			append(command->args, concat_string_type_tokens(arena, vec, i));
	}
	if(is_redirect_type(tok->type))
	{
		*i += 1;
		tok->content = concat_string_type_tokens(arena, vec, i);
		append(command->redirects, tok);
	}
}

//concatenates any unbroken sequence of string-type tokens to the return,
//starting at the index pointed to by i, updates the index as it goes along
//skips any leading empty tokens
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
	while (i < vec->size)
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
	while (++i < command->redirects->size)
	{
		ft_printf("redirects:\n");
		print_token((t_token *)command->redirects->get(command->redirects, i));
	}
	ft_printf("***\n");

}
