/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:51 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:30:52 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if expansion results in an empty string, change token to empty if it's 
//not followed by a string
void	empty_empty_expansion(t_vector *tokens, t_arena *arena)
{
	t_token	*tok;
	t_token	*next;
	int		i;

	i = -1;
	while (++i < tokens->size)
	{
		tok = tokens->get(tokens, i);
		if (tok->type == EXPANSION && strmatch(expand_variable(arena, \
tok->content), ""))
		{
			next = tokens->get(tokens, i + 1);
			if (!next || (next && (next->type == EMPTY || next->type == PIPE)))
				tok->type = EMPTY;
		}
	}
}

int	is_string_delimiter(char c)
{
	if (ft_isspace(c))
		return (1);
	if (c == '|' || c == '>' || c == '<' || c == '$' || c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_legal_expansion_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

ssize_t	expansion_length(char *s)
{
	ssize_t	length;

	length = 1;
	if (s[length] == '?' || s[length] == '_' || ft_isdigit(s[length]))
		return (2);
	while (is_legal_expansion_char(s[length]))
		++length;
	return (length);
}

ssize_t	dummy_length(char *s)
{
	if (*s == '>' && *(s + 1) == '>')
		return (2);
	if (*s == '<' && *(s + 1) == '<')
		return (2);
	return (1);
}
