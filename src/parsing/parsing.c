/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:27:39 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/08 14:23:26 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_empties(t_vector *vec)
{
	(void)vec;
}

t_command_table	*parse_vector_to_commands(t_arena *arena, t_vector *vec)
{
	t_command_table	*table;
	int				i;

	table = arena_alloc(arena, sizeof(t_command_table), NULL);
	if (!table)
		return (NULL);
	table->redirects = init_vector(1, NULL, arena);
	table->commands = init_vector(1, NULL, arena);
	remove_empties(vec);
	i = 0;
	while (i < vec->size)
		++i;
	return (table);
}


