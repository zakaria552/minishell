/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lengths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:45:11 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/07 15:20:01 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

ssize_t single_quote_length(char *s)
{
	ssize_t length;

	length = 1;
	while (s[length] && s[length] != '\'')
		++length;
	if (s[length] != '\'')
		return (-1);
	else
		++length;
	return (length);
}

ssize_t double_quote_length(char *s)
{
	ssize_t length;

	length = 1;
	while (s[length] && s[length] != '"')
		++length;
	if (s[length] != '"')
		return (-1);
	else
		++length;
	return (length);
}

static int is_string_delimiter(char c)
{
	if (ft_isspace(c))
		return (1);
	if (c == '|' || c == '>' || c == '<' || c == '$')
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
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

ssize_t expansion_length(char *s)
{
	ssize_t length;

	length = 1;
	while (s[length] && is_legal_expansion_char(s[length]))
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
