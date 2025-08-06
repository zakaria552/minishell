/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:18:41 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/07 13:36:51 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "vector.h"
#include "arena.h"

//token length counting functions for all types conform to this typedef
typedef ssize_t (*t_token_length_func)(char *);

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

t_vector	*tokenize_input(char *s, t_arena *arena);
ssize_t 	single_quote_length(char *s);
ssize_t 	double_quote_length(char *s);
ssize_t 	string_length(char *s);
ssize_t 	expansion_length(char *s);
ssize_t		empty_length(char *s);
ssize_t 	dummy_length(char *s);
void		print_token(t_token *tok);

#endif
