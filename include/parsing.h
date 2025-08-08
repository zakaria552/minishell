/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:18:41 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/08 14:14:10 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//forward declaration of used structures, 
//actual definitions in arena.h, vector.h and here, respectively
typedef struct s_arena		t_arena;
typedef struct s_vector		t_vector;

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

typedef struct s_command
{
	const char	*pathname;
	char		**argv;
}	t_command;

typedef struct s_redirect
{
	t_token_type	type;
	char			*content;
}	t_redirect;

typedef struct s_command_table
{
	t_vector	*redirects;
	t_vector	*commands;
}	t_command_table;

//tokenize.c
t_vector	*tokenize_input(char *s, t_arena *arena, char delimiter);

//token_lengths.c
ssize_t 	single_quote_length(char *s);
ssize_t 	double_quote_length(char *s);
ssize_t 	string_length(char *s);
ssize_t 	expansion_length(char *s);
ssize_t		empty_length(char *s);
ssize_t 	dummy_length(char *s);
int 		is_string_delimiter(char c);

//parsing.c
t_command_table	*parse_vector_to_commands(t_arena *arena, t_vector *vec);

//debug, remove before final submission
void		print_token(t_token *tok);

#endif
