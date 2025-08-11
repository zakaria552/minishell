/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraatika <nraatika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:18:41 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/07 16:30:34 by nraatika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//forward declaration of used structures, 
//actual definitions in arena.h and vector.h
typedef struct s_arena	t_arena;
typedef struct s_vector	t_vector;

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
	t_vector		*redirects;
	char 			**args;
}	t_token;

typedef struct cmd
{
	char *cmd;
	char **args;
	t_vector *redirects;
	int curr_pipe[2];
	int next_pipe[2];
	int pid;
	bool is_last_cmd;
} t_cmd;

typedef struct s_command
{
	char		*command;
	char		*options;
	t_vector	*arguments;
	char		*input_redir;
	char		*output_redir;
}	t_command;

t_vector	*tokenize_input(char *s, t_arena *arena);
ssize_t 	single_quote_length(char *s);
ssize_t 	double_quote_length(char *s);
ssize_t 	string_length(char *s);
ssize_t 	expansion_length(char *s);
ssize_t		empty_length(char *s);
ssize_t 	dummy_length(char *s);
void		print_token(t_token *tok);
int 		is_string_delimiter(char c);

#endif
