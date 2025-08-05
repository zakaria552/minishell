/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lengths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:45:11 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/05 12:29:06 by nraatika         ###   ########.fr       */
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
	return (length);
}

ssize_t string_length(char *s)
{
	ssize_t length;

	length = 1;
	while (s[length] && !ft_isspace(s[length]))
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

ssize_t dummy_length(char *s)
{
	(void)s;
	return (1);
}
