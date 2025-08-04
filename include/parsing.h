/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:18:41 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/07 13:22:03 by nraatika         ###   ########.fr       */
/*   Updated: 2025/08/04 14:22:51 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "arena.h"

typedef enum e_token_type
{
	EMPTY,
	PIPE,
	INPUT_REDIR,
	OUTPUT_REDIR,
	OUTPUT_APPEND,
	HERE_DOC,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	EXPANSION,
	STRING
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	int				read_chars;
}	t_token;

void	parse_input(char *s, t_arena *arena);
#endif
