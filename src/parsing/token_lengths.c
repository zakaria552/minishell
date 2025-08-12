/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lengths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:45:11 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/12 17:00:31 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static ssize_t	length_to_delim(char *s, char delim)
{
	ssize_t length;

	length = 1;
	while (s[length] && s[length] != delim)
		++length;
	if (s[length] != delim)
		return (-1);
	else
		++length;
	return (length);
}

ssize_t single_quote_length(char *s)
{
	return (length_to_delim(s, '\''));
}

ssize_t double_quote_length(char *s)
{
	return (length_to_delim(s, '"'));
}

int is_string_delimiter(char c)
{
	if (ft_isspace(c))
		return (1);
	if (c == '|' || c == '>' || c == '<' || c == '$' || c == '"' || c == '\'')
		return (1);
	return (0);
}

ssize_t string_length(char *s)
{
	ssize_t length;

	length = 1;
	while (s[length] && !is_string_delimiter(s[length]))
		++length;
	return (length);
}

static int	is_legal_expansion_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

ssize_t expansion_length(char *s)
{
	ssize_t length;

	length = 1;
	while (is_legal_expansion_char(s[length]))
		++length;
	return (length);
}

ssize_t	empty_length(char *s)
{
	ssize_t length;

	length = 1;
	while (s[length] && ft_isspace(s[length]))
		++length;
	return (length);
}

ssize_t dummy_length(char *s)
{
	if (*s == '>' && *(s + 1) == '>')
		return (2);
	if (*s == '<' && *(s + 1) == '<')
		return (2);
	return (1);
}
