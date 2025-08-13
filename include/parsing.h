/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:18:41 by nraatika          #+#    #+#             */
/*   Updated: 2025/08/12 16:24:30 by zfarah           ###   ########.fr       */
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
	t_vector		*redirects;
	char 			**args;
}	t_token;

typedef struct s_cmd
{
	char		*cmd;
	t_vector	*args;
	t_vector 	*redirects;
	int			fd_here_doc;
    int 		curr_pipe[2];
    int 		next_pipe[2];
    int 		pid;
    bool 		is_last_cmd;
}	t_cmd;

typedef struct s_redirect
{
	t_token_type	type;
	char			*content;
}	t_redirect;

//tokenize.c
t_vector	*tokenize_input(char *s, t_arena *arena, char delimiter);
//debug, remove before final submission
void		print_token(t_token *tok);

//token_lengths.c
ssize_t 	single_quote_length(char *s);
ssize_t 	double_quote_length(char *s);
ssize_t 	string_length(char *s);
ssize_t 	expansion_length(char *s);
ssize_t		empty_length(char *s);
ssize_t 	dummy_length(char *s);
int 		is_string_delimiter(char c);

//parsing.c
t_vector	*parse_tokens_to_commands(t_arena *arena, t_vector *vec);
char		*concat_string_type_tokens(t_arena *arena, t_vector *vec, int *i);
bool		is_string_type(t_token_type type);
bool		is_redirect_type(t_token_type type);
void		remove_empty_tokens(t_vector *vec);

//arena_strings.c
char	*arena_strdup(t_arena *arena, char *s);
char	*arena_strjoin(t_arena *arena, char *s1, char *s2);

//command.c
t_cmd	*init_command(t_arena *arena);
void	update_command(t_arena *arena, t_cmd *command, t_vector *vec, int *i);
//debug
void	print_command(t_cmd *command);
void	print_vector_commands(t_vector *vec);

#endif
