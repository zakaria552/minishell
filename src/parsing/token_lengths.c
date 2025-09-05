/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lengths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:30:48 by zfarah            #+#    #+#             */
/*   Updated: 2025/09/05 10:30:49 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	length_to_delim(char *s, char delim)
{
	ssize_t	length;

	length = 1;
	while (s[length] && s[length] != delim)
		++length;
	if (s[length] != delim)
		return (-1);
	else
		++length;
	return (length);
}

ssize_t	single_quote_length(char *s)
{
	return (length_to_delim(s, '\''));
}

ssize_t	double_quote_length(char *s)
{
	return (length_to_delim(s, '"'));
}

ssize_t	string_length(char *s)
{
	ssize_t	length;

	length = 1;
	while (s[length] && !is_string_delimiter(s[length]))
		++length;
	return (length);
}

ssize_t	empty_length(char *s)
{
	ssize_t	length;

	length = 1;
	while (s[length] && ft_isspace(s[length]))
		++length;
	return (length);
}
