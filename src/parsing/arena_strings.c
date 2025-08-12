/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:08:21 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/15 13:52:57 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*arena_strdup(t_arena *arena, char *s)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s) + 1;
	str = arena_alloc(arena, size * sizeof(char), s);
	return (str);
}

char	*arena_strjoin(t_arena *arena, char *s1, char *s2)
{
	char	*joint;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joint = arena_alloc(arena, (s1_len + s2_len + 1) * sizeof(char), NULL);
	if (!joint)
		return (NULL);
	ft_memmove(joint, (void *)s1, s1_len);
	ft_memmove(joint + s1_len, (void *)s2, s2_len);
	joint[s1_len + s2_len] = '\0';
	return (joint);
}

